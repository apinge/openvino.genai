#include "openvino/genai/llm_pipeline.hpp"
#include "openvino/genai/c_wrapper/llm_pipeline_c.h"

#ifdef __cplusplus
OPENVINO_EXTERN_C {
#endif

    LLMPipelineHandle CreateLLMPipeline(const char* models_path, const char* device) {
    return static_cast<LLMPipelineHandle>(new ov::genai::LLMPipeline(std::filesystem::path(models_path), std::string(device)));
}


    void LLMPipelineDestroy(LLMPipelineHandle handle) {
    if (handle) {
            ov::genai::LLMPipeline* pipeline = static_cast<ov::genai::LLMPipeline*>(handle);
            delete pipeline;
        }
    }
    void LLMPipelineGenerate(LLMPipelineHandle pipeline_handle, const char* inputs, char* output, int max_size,GenerationConfigHandle config_handle) {
        if(pipeline_handle) {
            ov::genai::LLMPipeline* pipeline = static_cast<ov::genai::LLMPipeline*>(pipeline_handle);
            std::string input_str(inputs);
            ov::genai::StringInputs input = {input_str};
            std::string results;
            if (config_handle) {
                ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(config_handle);
                results = pipeline->generate(input,*config);
            } else {
                results = pipeline->generate(input);
            }
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


#ifdef __cplusplus
    }
#endif