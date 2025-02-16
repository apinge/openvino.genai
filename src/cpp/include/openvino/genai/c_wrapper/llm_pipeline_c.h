// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief This is a header file for OpenVINO GenAI C API, which is a C wrapper for  ov::genai::LLMPipeline class.
 *
 * @file llm_pipeline_c.h
 */

#pragma once
#include "generation_config_c.h"
#ifdef __cplusplus
OPENVINO_EXTERN_C {
#endif

typedef void* LLMPipelineHandle;
    OPENVINO_GENAI_EXPORTS LLMPipelineHandle CreateLLMPipeline(const char* models_path, const char* device);
    OPENVINO_GENAI_EXPORTS void LLMPipelineDestroy(LLMPipelineHandle handle);
    OPENVINO_GENAI_EXPORTS void LLMPipelineGenerate(LLMPipelineHandle handle,
                                                    const char* inputs,
                                                    char* output,
                                                    int max_size,
                                                    GenerationConfigHandle config);
    OPENVINO_GENAI_EXPORTS void LLMPipelineStartChat(LLMPipelineHandle handle);
    OPENVINO_GENAI_EXPORTS void LLMPipelineFinishCaht(LLMPipelineHandle handle);


#ifdef __cplusplus
}
#endif
