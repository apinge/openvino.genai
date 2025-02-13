#include "openvino/genai/llm_pipeline.hpp"
#include "openvino/genai/genai_c_api.h"

extern "C" {

    LLMPipelineHandle CreateLLMPipeline(const char* models_path, const char* device) {
    return static_cast<LLMPipelineHandle>(new ov::genai::LLMPipeline(std::filesystem::path(models_path), std::string(device)));
}


    void LLMPipelineDestroy(LLMPipelineHandle handle) {
    if (handle) {
            ov::genai::LLMPipeline* pipeline = static_cast<ov::genai::LLMPipeline*>(handle);
            delete pipeline;
        }
    }
    void LLMPipelineGenerate(LLMPipelineHandle handle, const char* inputs, char* output, int max_size) {
        if(handle) {
            ov::genai::LLMPipeline* pipeline = static_cast<ov::genai::LLMPipeline*>(handle);
            std::string input_str(inputs);
            ov::genai::StringInputs input = {input_str};
            std::string results = pipeline->generate(input);

            strncpy(output, results.c_str(),max_size -1);
            output[max_size - 1] = '\0';  

        }
    }
    void LLMPipelineStartChat(LLMPipelineHandle handle) {
        if (handle) {
            ov::genai::LLMPipeline* pipeline = static_cast<ov::genai::LLMPipeline*>(handle);
            pipeline->start_chat();
        }
     }
    void LLMPipelineFinishCaht(LLMPipelineHandle handle){
          if (handle) {
                ov::genai::LLMPipeline* pipeline = static_cast<ov::genai::LLMPipeline*>(handle);
                pipeline->finish_chat();
          }
        }
    }  // extern "C"