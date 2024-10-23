#ifndef _UTIL
#define _UTIL

#include <iostream>
#include <sstream>
#include <vector>
#include "openvino/genai/llm_pipeline.hpp"
#include "openvino/genai/visual_language/pipeline.hpp"

#include "openvino/runtime/intel_gpu/properties.hpp"
#include "openvino/runtime/tensor.hpp"
#include "stb_image.h"
#include "embeddings.hpp"
#include "reranker.hpp"
#include "state.hpp"
#include <queue>
#include "blip.hpp"
#include "db_pgvector.hpp"

#ifdef _WIN32
#include "windows.h"
#include <codecvt>
#endif

class util {
public:

    static ov::Tensor string_to_tensor(const std::string &image_data, int x, int y, int channels, int desired_channels) {
        unsigned char* image = stbi_load_from_memory(
            reinterpret_cast<const unsigned char*>(image_data.data()), 
            image_data.size(), 
            &x, 
            &y, 
            &channels, 
            desired_channels
        );
        if (!image) {
            throw std::runtime_error("Failed to decode image.");
        }
        struct SharedImageAllocator {
            unsigned char* image;
            int channels, height, width;
            void* allocate(size_t bytes, size_t) const {
                if (channels * height * width == bytes) {
                    return image;
                }
                throw std::runtime_error{"Unexpected number of bytes was requested to allocate."};
            }
            void deallocate(void*, size_t bytes, size_t) {
                if (channels * height * width != bytes) {
                    throw std::runtime_error{"Unexpected number of bytes was requested to deallocate."};
                }
                std::free(image);
                image = nullptr;
            }
            bool is_equal(const SharedImageAllocator& other) const noexcept {return this == &other;}
        };
        return ov::Tensor(
            ov::element::u8,
            ov::Shape{1, size_t(desired_channels), size_t(y), size_t(x)},
            SharedImageAllocator{image, desired_channels, y, x}
        );
    }

    struct Args {
        std::string llm_model_path = "";
        std::string llm_device = "CPU";
        std::string vlm_model_path = "";
        std::string vlm_device = "CPU";
        std::string embedding_model_path = "";
        std::string image_embedding_model_path = "";
        std::string image_embedding_device = "CPU";
        std::string embedding_device = "CPU";
        std::string reranker_model_path = "";
        std::string reranker_device = "CPU";
        std::string db_connection = "user=postgres host=localhost password=openvino port=5432 dbname=postgres";
        std::string rag_connection = "127.0.0.1:7890";
        int max_new_tokens = 64;
        bool do_sample = false;
        bool enable_multi_round_chat = false;
        int top_k = 0;
        float top_p = 0.7;
        float temp = 0.95;
        float repeat_penalty = 1.0;
        bool verbose = false;
    };

    class llmBackend{
        public:
            
            std::shared_ptr<ov::genai::LLMPipeline> llm_pointer;
            std::queue<std::string> chat_buffer;
            int max_new_tokens=32;

            void infer_thread(){
                auto config = llm_pointer->get_generation_config();
                config.max_new_tokens = max_new_tokens;
    
                auto streamer = [this](std::string subword) {
                    // std::cout << "subword: " << subword << std::endl;
                    this->chat_buffer.push(subword);
                    return false;
                };
                llm_pointer->generate(prompt, config, streamer);      
                this->chat_buffer.push("zheshibiaozhifu");     
   
            }

            void start_infer(){
                std::thread infer_thread(&llmBackend::infer_thread, this);
                infer_thread.detach();
            }

            void get_prompt(std::string new_prompt){
                this->prompt = new_prompt;
                this->llm_backend_state = State::RUNNING;
            }

            void set_config(Args args){
                this->max_new_tokens = args.max_new_tokens;
            }
        
        private:
            std::string prompt;
            State llm_backend_state;
    };

    class vlmBackend{
        public:
            
            std::shared_ptr<ov::genai::VLMPipeline> vlm_pointer;
            std::queue<std::string> chat_buffer;
            int max_new_tokens=32;

            void infer_thread(){
                auto config = vlm_pointer->get_generation_config();
                config.max_new_tokens = max_new_tokens;
    
                auto streamer = [this](std::string subword) {
                    // std::cout << "subword: " << subword << std::endl;
                    this->chat_buffer.push(subword);
                    return false;
                };
                vlm_pointer->generate(prompt, ov::genai::image(image), ov::genai::streamer(streamer));  
                this->chat_buffer.push("zheshibiaozhifu");     
   
            }

            void start_infer(){
                std::thread infer_thread(&vlmBackend::infer_thread, this);
                infer_thread.detach();
            }

            void get_prompt(std::string new_prompt){
                this->prompt = new_prompt;
                this->vlm_backend_state = State::RUNNING;
            }
            
            void get_image(ov::Tensor new_image){
                this->image = new_image;
                this->vlm_backend_state = State::RUNNING;
            }

            bool check_image(){
                return bool(this->image);
            }
            void set_config(Args args){
                this->max_new_tokens = args.max_new_tokens;
            }
        
        private:
            ov::Tensor image;
            std::string prompt;
            State vlm_backend_state;
    };

    struct ServerContext {
        std::shared_ptr<vlmBackend> vlm_stream_pointer;
        std::shared_ptr<llmBackend> llm_stream_pointer;
        std::shared_ptr<Embeddings> embedding_pointer;
        std::shared_ptr<BlipModel> image_embeddings_pointer;
        std::shared_ptr<Reranker> reranker_pointer;
        std::shared_ptr<DBPgvector> db_pgvector_pointer;

        util::Args args;

        State server_state = State::STOPPED;
        State embedding_state = State::STOPPED;
        State image_embeddings_state = State::STOPPED;
        State llm_state = State::STOPPED;
        State vlm_state = State::STOPPED;
        State db_state = State::STOPPED;

        size_t chunk_num = 0;
        std::vector<std::string> retrieval_prompt_history;
        
        std::vector<std::string> retrieval_res;

        size_t image_num = 0;

        ServerContext(Args arg_): args(arg_){}
    };



    static auto usage(const std::string& prog) -> void {
        std::cout
            << "Usage: " << prog << " [options]\n"
            << "\n"
            << "options:\n"
            << "  -h,    --help                        Show this help message and exit\n"
            << "  --llm_model_path          PATH        Directory contains OV LLM model and tokenizers\n"
            << "  --enable_multi_round_chat BOOL        Specify whether do multi-round chat (default: False)\n"
            << "  --llm_device              STRING      Specify which device used for llm inference\n"
            << "  --embedding_model_path    PATH        Directory contains OV Bert model and tokenizers\n"
            << "  --embedding_device        STRING      Specify which device used for bert inference\n"
            << "  --image_embedding_model_path   PATH        Directory contains OV blip vision model and projection model\n"
            << "  --image_embedding_device       STRING      Specify which device used for blip inference\n"
            << "  --reranker_model_path     PATH        Directory contains OV Reranker model and tokenizers\n"
            << "  --reranker_device         STRING      Specify which device used for reranker inference\n"
            << "  --db_connection           STRING      Specify which user, host, password, port, dbname\n"
            << "  --rag_connection          STRING      Specify host:port(default: \"127.0.0.1:7890\")\n"
            << "  --max_new_tokens          N           Specify max new generated tokens (default: 32)\n"
            << "  --do_sample               BOOL        Specify whether do random sample (default: False)\n"
            << "  --top_k                   N           Specify top-k parameter for sampling (default: 0)\n"
            << "  --top_p                   N           Specify top-p parameter for sampling (default: 0.7)\n"
            << "  --temperature             N           Specify temperature parameter for sampling (default: 0.95)\n"
            << "  --repeat_penalty          N           Specify penalize sequence of tokens (default: 1.0, means no "
               "repeat "
               "penalty)\n"
            << "  --verbose                 BOOL        Display verbose output including config/system/performance "
               "info\n";
    }

    static auto parse_args(const std::vector<std::string>& argv) -> Args {
        Args args;

        for (size_t i = 1; i < argv.size(); i++) {
            const std::string& arg = argv[i];

            if (arg == "-h" || arg == "--help") {
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            } else if (arg == "--llm_model_path") {
                args.llm_model_path = argv[++i];
            } else if (arg == "--llm_device") {
                args.llm_device = argv[++i];
            } else if (arg == "--vlm_model_path") {
                args.vlm_model_path = argv[++i];
            } else if (arg == "--vlm_device") {
                args.vlm_device = argv[++i];
            } else if (arg == "--db_connection") {
                args.db_connection = argv[++i];
            } else if (arg == "--rag_connection") {
                args.rag_connection = argv[++i];
            } else if (arg == "--embedding_model_path") {
                args.embedding_model_path = argv[++i];
            } else if (arg == "--embedding_device") {
                args.embedding_device = argv[++i];
            } else if (arg == "--image_embedding_model_path") {
                args.image_embedding_model_path = argv[++i];
            } else if (arg == "--image_embedding_device") {
                args.image_embedding_device = argv[++i];
            } else if (arg == "--reranker_model_path") {
                args.reranker_model_path = argv[++i];
            } else if (arg == "--reranker_device") {
                args.reranker_device = argv[++i];
            } else if (arg == "--max_new_tokens") {
                args.max_new_tokens = std::stoi(argv[++i]);
            } else if (arg == "--do_sample") {
                args.do_sample = true;
            } else if (arg == "--top_k") {
                args.top_k = std::stoi(argv[++i]);
            } else if (arg == "--top_p") {
                args.top_p = std::stof(argv[++i]);
            } else if (arg == "--temperature") {
                args.temp = std::stof(argv[++i]);
            } else if (arg == "--repeat_penalty") {
                args.repeat_penalty = std::stof(argv[++i]);
            } else if (arg == "--verbose") {
                args.verbose = true;
            } else if (arg == "--enable_multi_round_chat") {
                args.enable_multi_round_chat = true;
            } else {
                std::cerr << "Unknown argument: " << arg << std::endl;
                usage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }

        return args;
    }

    static auto parse_args(int argc, char** argv) -> Args {
        std::vector<std::string> argv_vec;
        argv_vec.reserve(argc);


#ifdef _WIN32
        LPWSTR* wargs = CommandLineToArgvW(GetCommandLineW(), &argc);

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        for (int i = 0; i < argc; i++) {
            argv_vec.emplace_back(converter.to_bytes(wargs[i]));
        }

        LocalFree(wargs);
#else
        for (int i = 0; i < argc; i++) {
            argv_vec.emplace_back(argv[i]);
        }
#endif

        return parse_args(argv_vec);
    }
};

#endif