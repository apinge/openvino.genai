// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//
#include "openvino/genai/c_wrapper/llm_pipeline_c.h"
#include "common_c.hpp"
#include "openvino/genai/c_wrapper/generation_config_c.h"
#include "openvino/genai/generation_config.hpp"
#include "openvino/genai/llm_pipeline.hpp"

#ifdef __cplusplus
OPENVINO_EXTERN_C {
#endif
    DecodedResultsHandle* CreateDecodedResults() {
        DecodedResultsHandle* results = new DecodedResultsHandle;
        results->object = std::make_shared<ov::genai::DecodedResults>();
        return results;
    }
    void DestroyDecodedResults(DecodedResultsHandle* results) {
        if (results) {
            delete results;
        }
    }
    void DecodedeResultsGetPerfMetrics(DecodedResultsHandle * results, PerfMetricsHandle* metrics) {
        if (results && metrics) {
            metrics->object = std::make_shared<ov::genai::PerfMetrics>(results->object->perf_metrics);
        }
    }

    LLMPipelineHandle* CreateLLMPipeline(const char* models_path, const char* device) {
        LLMPipelineHandle* pipe = new LLMPipelineHandle;
        pipe->object =
            std::make_shared<ov::genai::LLMPipeline>(std::filesystem::path(models_path), std::string(device));
        return pipe;
    }

    void DestroyLLMPipeline(LLMPipelineHandle * pipe) {
        if (pipe) {
            delete pipe;
        }
    }
    void LLMPipelineGenerate(LLMPipelineHandle * pipe,
                             const char* inputs,
                             char* output,
                             int max_size,
                             GenerationConfigHandle* config) {
        if (pipe) {
            std::string input_str(inputs);
            ov::genai::StringInputs input = {input_str};
            std::string results;
            if (config) {
                results = pipe->object->generate(input, *(config->object));
            } else {
                results = pipe->object->generate(input);
            }
            strncpy(output, results.c_str(), max_size - 1);
            output[max_size - 1] = '\0';
        }
    }
    void LLMPipelineGenerateDecodeResults(LLMPipelineHandle* pipe,
                                     const char* inputs,
                                     DecodedResultsHandle* results,
                                     GenerationConfigHandle* config) {
        if (pipe) {
            std::string input_str(inputs);
            ov::genai::StringInputs input = {input_str};
            if (config) {
                *results->object = pipe->object->generate(input, *(config->object));
            } else {
                *results->object = pipe->object->generate(input);
            }
        }
    }
    void LLMPipelineStartChat(LLMPipelineHandle * pipe) {
        if (pipe) {
            pipe->object->start_chat();
        }
    }
    void LLMPipelineFinishChat(LLMPipelineHandle * pipe) {
        if (pipe) {
            pipe->object->finish_chat();
        }
    }
    GenerationConfigHandle* LLMPipelineGetGeneratonConfig(LLMPipelineHandle * pipe) {
        if (pipe) {
            GenerationConfigHandle* config = new GenerationConfigHandle;
            config->object = std::make_shared<ov::genai::GenerationConfig>(pipe->object->get_generation_config());
            return config;
        }
        return NULL;
    }
    void LLMPipelineSetGeneratonConfig(LLMPipelineHandle * pipe, GenerationConfigHandle * config) {
        if (pipe && config) {
            pipe->object->set_generation_config(*(config->object));
        }
    }

#ifdef __cplusplus
}
#endif