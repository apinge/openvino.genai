#include "openvino/genai/genai_c_api.hpp"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    //if (argc < 3) {
    //    fprintf(stderr, "Usage: %s <MODEL_DIR> \"<PROMPT>\"\n", argv[0]);
    //    return EXIT_FAILURE;
    //}
    printf("This is C API for OpenVINO GenAI\n");
    const char* model_dir = "C:\\Users\\gta\\source\\repos\\tiny-llama-1.1b-chat_OV_FP16-INT8_ASYM";
    const char* prompt = "How many r letters are there in the word strawberry?";

    LLMPipelineHandle pipeline = CreateLLMPipeline(model_dir, "CPU");
    if (pipeline == NULL) {
        fprintf(stderr, "Failed to create LLM pipeline\n");
        return EXIT_FAILURE;
    }

    char output[1024];
    LLMPipelineGenerate(pipeline, prompt, output, sizeof(output));

    printf("Generated text: %s\n", output);

    LLMPipelineDestroy(pipeline);
    // Add your code logic here

    return EXIT_SUCCESS;
}
