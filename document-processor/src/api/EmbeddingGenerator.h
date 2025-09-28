//
// Created by Mitchell on 9/23/2025.
//

#ifndef DOCUMENT_PROCESSOR_EMBEDDINGGENERATOR_H
#define DOCUMENT_PROCESSOR_EMBEDDINGGENERATOR_H
#include <string>
#include <vector>

struct DocumentChunk;

class EmbeddingGenerator {
    std::string api_token;
    std::string api_url;

public:
    EmbeddingGenerator(std::string &api_token, const std::string &api_url="https://api.openai.com/v1/embeddings");
    void add_embeddings_to_chunks(std::vector<DocumentChunk> &chunks);
    std::vector<float> generate_embedding(const std::string &text);
private:
    std::vector<std::vector<float>> generate_batch_embeddings(const std::vector<std::string> &texts);

};


#endif //DOCUMENT_PROCESSOR_EMBEDDINGGENERATOR_H