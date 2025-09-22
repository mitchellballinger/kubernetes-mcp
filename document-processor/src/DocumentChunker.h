//
// Created by Mitchell on 9/21/2025.
//

#ifndef DOCUMENT_PROCESSOR_DOCUMENTCHUNKER_H
#define DOCUMENT_PROCESSOR_DOCUMENTCHUNKER_H
#include <string>
#include <vector>

struct DocumentChunk {
    std::string text;
    std::string source_file;
    std::string header;
    int chunk_index;
};

class DocumentChunker {
public:
    DocumentChunker();

    std::vector<DocumentChunk> extract_chunks(std::string &contents, std::string &file_path);
};


#endif //DOCUMENT_PROCESSOR_DOCUMENTCHUNKER_H