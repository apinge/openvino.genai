// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief This is a header file for OpenVINO GenAI C API, which is a C wrapper for  ov::genai::GenerationConfig class.
 *
 * @file generation_config_c.h
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "../visibility.hpp"


#ifdef __cplusplus
OPENVINO_EXTERN_C {
#endif


typedef enum { EARLY, HEURISTIC, NEVER } StopCriteria;
// ov::genai::GenerationConfig
typedef void* GenerationConfigHandle;
OPENVINO_GENAI_EXPORTS GenerationConfigHandle CreateGenerationConfig();
OPENVINO_GENAI_EXPORTS GenerationConfigHandle CreateGenerationConfigFromJson(const char* json_path);
OPENVINO_GENAI_EXPORTS void DestroyGenerationConfig(GenerationConfigHandle handle);

// Generic
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetMaxNewTokens(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetMaxLength(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetIgnoreEOS(GenerationConfigHandle handle, bool value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetMinNewTokens(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetEcho(GenerationConfigHandle handle, bool value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetLogProbs(GenerationConfigHandle handle, size_t value);

OPENVINO_GENAI_EXPORTS void GenerationConfig_SetStopStrings(GenerationConfigHandle handle,
                                                            const char* strings[],
                                                            size_t count);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetIncludeStopStrInOutput(GenerationConfigHandle handle, bool value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetStopTokenIds(GenerationConfigHandle handle,
                                                             int64_t* token_ids,
                                                             size_t token_ids_num);

// Beam Search
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetNumBeamGroups(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetNumBeams(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetDiversityPenalty(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetLengthPenalty(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetNumReturnSequences(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetNoRepeatNgramSize(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void SetStopCriteria(GenerationConfigHandle handle, StopCriteria value);

OPENVINO_GENAI_EXPORTS void GenerationConfig_SetTemperature(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetTopP(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetTopK(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetDoSample(GenerationConfigHandle handle, bool value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetRepetitionPenalty(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetPresencePenalty(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetFrequencyPenalty(GenerationConfigHandle handle, float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetRngSeed(GenerationConfigHandle handle, size_t value);

OPENVINO_GENAI_EXPORTS void GenerationConfig_SetAssistantConfidenceThreshold(GenerationConfigHandle handle,
                                                                             float value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetNumAssistantTokens(GenerationConfigHandle handle, size_t value);
OPENVINO_GENAI_EXPORTS void GenerationConfig_SetMaxNgramSize(GenerationConfigHandle handle, size_t value);

OPENVINO_GENAI_EXPORTS void GenerationConfig_SetEOSTokenID(GenerationConfigHandle handle, int64_t id);

OPENVINO_GENAI_EXPORTS size_t GenerationConfig_GetMaxNewTokens(GenerationConfigHandle handle);
OPENVINO_GENAI_EXPORTS bool GenerationConfig_IsGreedyDecoding(GenerationConfigHandle handle);
OPENVINO_GENAI_EXPORTS bool GenerationConfig_IsBeamSearch(GenerationConfigHandle handle);
OPENVINO_GENAI_EXPORTS bool GenerationConfig_IsMultinomial(GenerationConfigHandle handle);
OPENVINO_GENAI_EXPORTS bool GenerationConfig_IsAssistingGeneration(GenerationConfigHandle handle);
OPENVINO_GENAI_EXPORTS bool GenerationConfig_IsPromptLookup(GenerationConfigHandle handle);
OPENVINO_GENAI_EXPORTS void GenerationConfig_Validate(GenerationConfigHandle handle);

#ifdef __cplusplus
}
#endif