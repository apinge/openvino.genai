#ifndef GENAI_C_API_H
#define GENAI_C_API_H

#include "visibility.hpp"

#ifdef _WIN32
//#define DllImport   __declspec( dllimport )
#    define DllExport __declspec(dllexport)
#else  // only consider linux
#    define DllExport __attribute__((visibility("default")))
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef void* LLMPipelineHandle;
DllExport LLMPipelineHandle CreateLLMPipeline(const char* models_path, const char* device);
DllExport void LLMPipelineDestroy(LLMPipelineHandle handle);
DllExport void LLMPipelineGenerate(LLMPipelineHandle handle,
                                               const char* inputs,
                                               char* output,
                                               int max_size);

#ifdef __cplusplus
 }
#endif

#endif // GENAI_C_API_H
