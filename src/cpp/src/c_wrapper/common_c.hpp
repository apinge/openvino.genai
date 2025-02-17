// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include "openvino/genai/generation_config.hpp"
#include "openvino/genai/llm_pipeline.hpp"
#include "openvino/genai/visibility.hpp"

#ifdef __cplusplus
OPENVINO_EXTERN_C {
#endif

    /**
     * @struct GenerationConfigOpaque
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
    /**
     * @struct PerfMetricsOpaque
     * @brief This is an interface of ov::genai::PerfMetrics
     */
    struct PerfMetricsOpaque {
        std::shared_ptr<ov::genai::PerfMetrics> object;
    };
    /**
     * @struct DecodedResultsOpaque
     * @brief This is an interface of ov::genai::DecodedResults
     */
    struct DecodedResultsOpaque {
        std::shared_ptr<ov::genai::DecodedResults> object;
    };

#ifdef __cplusplus
}
#endif
