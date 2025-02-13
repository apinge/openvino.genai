#ifndef GENAI_C_API_H
#define GENAI_C_API_H

#include "visibility.hpp"


#ifdef __cplusplus
extern "C" {
#endif

typedef void* LLMPipelineHandle;
OPENVINO_GENAI_EXPORTS LLMPipelineHandle CreateLLMPipeline(const char* models_path, const char* device);
OPENVINO_GENAI_EXPORTS void LLMPipelineDestroy(LLMPipelineHandle handle);
OPENVINO_GENAI_EXPORTS void LLMPipelineGenerate(LLMPipelineHandle handle,
                                               const char* inputs,
                                               char* output,
                                               int max_size);
OPENVINO_GENAI_EXPORTS void LLMPipelineStartChat(LLMPipelineHandle handle);
OPENVINO_GENAI_EXPORTS void LLMPipelineFinishCaht(LLMPipelineHandle handle);

#ifdef __cplusplus
 }
#endif

#endif // GENAI_C_API_H
