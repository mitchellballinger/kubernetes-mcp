//
// Created by Mitchell on 9/21/2025.
//

#include "DocumentChunker.h"
#include <string>
#include <vector>
#include <regex>

using std::string;
using std::vector;
using std::regex;
using std::sregex_iterator;
using std::pair;

DocumentChunker::DocumentChunker() {

}

vector<DocumentChunk> DocumentChunker::extract_chunks(string &contents, string &file_path) {
    regex header_pattern(R"(^## (.+)$)");

    sregex_iterator iter(contents.begin(), contents.end(), header_pattern);
    sregex_iterator end;

    vector<DocumentChunk> chunks;

    // Collect all match positions and header texts
    vector<pair<size_t, string>> headers;
    for (; iter != end; ++iter) {
        size_t pos = iter->position();
        string header_text = (*iter)[1].str();
        headers.push_back({pos, header_text});
    }

    if (!headers.empty()) {
        string overview_content = contents.substr(0, headers[0].first);
        DocumentChunk chunk;
        chunk.text = overview_content;
        chunk.chunk_index = 0;
        chunk.header = "Overview";
        chunk.source_file = file_path;
        chunks.push_back(chunk);
    }

    for (int i = 0; i < headers.size(); ++i) {
        size_t start_pos = headers[i].first;
        size_t end_pos = (i + 1 < headers.size()) ? headers[i + 1].first : contents.length();

        string chunk_text = contents.substr(start_pos, end_pos - start_pos);
        string header_text = headers[i].second;

        DocumentChunk chunk;
        chunk.text = chunk_text;
        chunk.chunk_index = i + 1;
        chunk.header = header_text;
        chunk.source_file = file_path;

        chunks.push_back(chunk);
    }

    return chunks;
}
