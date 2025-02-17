// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief This is a header file for OpenVINO GenAI C API
 *
 * @file type_c.h
 */

#pragma once
#include "openvino/genai/visibility.hpp"
#include "openvino/genai/llm_pipeline.hpp"
#include "openvino/genai/generation_config.hpp"

#ifdef __cplusplus
OPENVINO_EXTERN_C {
#endif

     /**
     * @struct LLMPipelineOpaque
     * @brief This is an interface of ov::genai::GenerationConfig
     */
    struct GenerationConfigOpaque {
        std::shared_ptr<ov::genai::GenerationConfig> object;
    };

      /**
     * @struct LLMPipelineOpaque
     * @brief This is an interface of ov::genai::LLMPipeline
     */
    struct LLMPipelineOpaque {
        std::shared_ptr<ov::genai::LLMPipeline> object;
    };

    struct PerfMetricsOpaque {
        std::shared_ptr<ov::genai::PerfMetrics> object;
    };

    struct DecodedResultsOpaque {
        std::shared_ptr<ov::genai::DecodedResults> object;
    };

    struct EncodedResultsOpaque {
        std::shared_ptr<ov::genai::EncodedResults> object;
    };

#ifdef __cplusplus
    }
#endif
