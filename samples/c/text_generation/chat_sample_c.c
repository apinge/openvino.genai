#include "openvino/genai/genai_c_api.hpp"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROMPT_LENGTH 256
#define MAX_OUTPUT_LENGTH 1024

void streamer(const char* word) {
    printf("%s", word);
    fflush(stdout);
}
int main(int argc, char* argv[]) {
    printf("This is a C API example for OpenVINO GenAI.\n");
    if (argc !=2 ) {
        fprintf(stderr, "Usage: %s <MODEL_DIR> \"<PROMPT>\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    char prompt[MAX_PROMPT_LENGTH], output[MAX_OUTPUT_LENGTH];
    const char* models_path = argv[1];
    const char* device = "CPU";  // GPU, NPU can be used as well
    LLMPipelineHandle pipeline = CreateLLMPipeline(models_path, "CPU");
    if (pipeline == NULL) {
        fprintf(stderr, "Failed to create LLM pipeline\n");
        return EXIT_FAILURE;
    }
    // int max_new_tokens = 100;

    LLMPipelineStartChat(pipeline);
    printf("question:\n");
    while (fgets(prompt, MAX_PROMPT_LENGTH, stdin)) {
        prompt[strcspn(prompt, "\n")] = 0;

        LLMPipelineGenerate(pipeline, prompt, output, sizeof(output));
        streamer(output);

        printf("\n----------\nquestion:\n");
    }
    LLMPipelineStartChat(pipeline);

    return EXIT_SUCCESS;
}
