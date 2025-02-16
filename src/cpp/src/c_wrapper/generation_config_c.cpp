#include "openvino/genai/generation_config.hpp"
#include "openvino/genai/c_wrapper/generation_config_c.h"


#ifdef __cplusplus 
OPENVINO_EXTERN_C {
#endif

    GenerationConfigHandle CreateGenerationConfig() {
        return static_cast<GenerationConfigHandle>(new ov::genai::GenerationConfig());
    }
    GenerationConfigHandle CreateGenerationConfigFromJson(const char* json_path) {
        return static_cast<GenerationConfigHandle>(new ov::genai::GenerationConfig(json_path));
    }
    void DestroyGenerationConfig(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            delete config;
        }
    }

    // Generic
    void GenerationConfig_SetMaxNewTokens(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->max_new_tokens = value;
        }
    }
    void GenerationConfig_SetMaxLength(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->max_length = value;
        }
    }
    void GenerationConfig_SetIgnoreEOS(GenerationConfigHandle handle, bool value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->ignore_eos = value;
        }
    }
    void GenerationConfig_SetMinNewTokens(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->min_new_tokens = value;
        }
    }
    void GenerationConfig_SetEcho(GenerationConfigHandle handle, bool value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->echo = value;
        }
    }
    void GenerationConfig_SetLogProbs(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->logprobs = value;
        }
    }

    void GenerationConfig_SetIncludeStopStrInOutput(GenerationConfigHandle handle, bool value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->include_stop_str_in_output = value;
        }
    }
    void GenerationConfig_SetStopStrings(GenerationConfigHandle handle, const char* strings[], size_t count) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            std::set<std::string> stop_strings;
            for (size_t i = 0; i < count; i++) {
                stop_strings.insert(strings[i]);
            }
            config->stop_strings = stop_strings;
        }
    }
    void GenerationConfig_SetStopTokenIds(GenerationConfigHandle handle, int64_t * token_ids, size_t token_ids_num) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            std::set<int64_t> stop_token_ids;
            for (size_t i = 0; i < token_ids_num; i++) {
                stop_token_ids.insert(token_ids[i]);
            }
            config->stop_token_ids = stop_token_ids;
        }
    }
    // Beam Search
    void GenerationConfig_SetNumBeamGroups(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->num_beam_groups = value;
        }
    }
    void GenerationConfig_SetNumBeams(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->num_beams = value;
        }
    }
    void GenerationConfig_SetDiversityPenalty(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->diversity_penalty = value;
        }
    }
    void GenerationConfig_SetLengthPenalty(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->length_penalty = value;
        }
    }
    void GenerationConfig_SetNumReturnSequences(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->num_return_sequences = value;
        }
    }
    void GenerationConfig_SetNoRepeatNgramSize(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->no_repeat_ngram_size = value;
        }
    }

    void SetStopCriteria(GenerationConfigHandle handle, StopCriteria value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->stop_criteria = static_cast<ov::genai::StopCriteria>(value);
        }
    }

    void GenerationConfig_SetTemperature(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->temperature = value;
        }
    }
    void GenerationConfig_SetTopP(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->top_p = value;
        }
    }
    void GenerationConfig_SetTopK(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->top_k = value;
        }
    }
    void GenerationConfig_SetDoSample(GenerationConfigHandle handle, bool value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->do_sample = value;
        }
    }
    void GenerationConfig_SetRepetitionPenalty(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->repetition_penalty = value;
        }
    }
    void GenerationConfig_SetPresencePenalty(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->presence_penalty = value;
        }
    }
    void GenerationConfig_SetFrequencyPenalty(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->frequency_penalty = value;
        }
    }
    void GenerationConfig_SetRngSeed(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->rng_seed = value;
        }
    }

    void GenerationConfig_SetAssistantConfidenceThreshold(GenerationConfigHandle handle, float value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->assistant_confidence_threshold = value;
        }
    }
    void GenerationConfig_SetNumAssistantTokens(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->num_assistant_tokens = value;
        }
    }
    void GenerationConfig_SetMaxNgramSize(GenerationConfigHandle handle, size_t value) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->max_ngram_size = value;
        }
    }

    void GenerationConfig_SetEOSTokenID(GenerationConfigHandle handle, int64_t id) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->eos_token_id = id;
        }
    }

    size_t GenerationConfig_GetMaxNewTokens(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            return config->max_new_tokens;
        }
        return 0;
    }
    bool GenerationConfig_IsGreedyDecoding(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            return config->is_greedy_decoding();
        }
        return false;
    }
    bool GenerationConfig_IsBeamSearch(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            return config->is_beam_search();
        }
        return false;
    }
    bool GenerationConfig_IsMultinomial(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            return config->is_multinomial();
        }
        return false;
    }
    bool GenerationConfig_IsAssistingGeneration(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            return config->is_assisting_generation();
        }
        return false;
    }
    bool GenerationConfig_IsPromptLookup(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            return config->is_prompt_lookup();
        }
        return false;
    }
    void GenerationConfig_Validate(GenerationConfigHandle handle) {
        if (handle) {
            ov::genai::GenerationConfig* config = static_cast<ov::genai::GenerationConfig*>(handle);
            config->validate();
        }
    }


#ifdef __cplusplus
}
#endif