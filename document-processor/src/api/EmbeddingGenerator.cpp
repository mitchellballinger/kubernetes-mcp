//
// Created by Mitchell on 9/23/2025.
//

#include "EmbeddingGenerator.h"
#include <vector>
#include <string>

#include "../DocumentChunker.h"

using std::vector;
using std::string;

EmbeddingGenerator::EmbeddingGenerator(std::string &api_token, const std::string &api_url) {
    this->api_token = api_token;
    if (api_url != "") {
        this->api_url = api_url;
    }
}

/**
 * Split the embeddings into chunks of size 2048, since you can only send
 * 2048 input texts to open ai's API for embeddings
 * Send all 2048 chunks and then move onto new batch
 * @param chunks list of all document chunk objects that have the chunk text
 */
void EmbeddingGenerator::add_embeddings_to_chunks(std::vector<DocumentChunk> &chunks) {
    const size_t BATCH_SIZE = 2048;

    for (size_t i = 0; i < chunks.size(); i+=BATCH_SIZE) {
        vector<string> batch_texts;
        for (size_t j = i; j < std::min(i + BATCH_SIZE, chunks.size()); ++j) {
            batch_texts.push_back(chunks[j].text);
        }
    }
}

vector<float> EmbeddingGenerator::generate_embedding(const string &text) {
    vector<float> embedding;
    return embedding;
}

vector<vector<float>> EmbeddingGenerator::generate_batch_embeddings(const vector<string> &texts) {
    vector<vector<float>> batches;
    return batches;
}







