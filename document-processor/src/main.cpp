
#include "api/GitHubClient.h"
#include "Cleaner.h"

#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <fstream>

#include "DocumentChunker.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::vector;

int main() {

    ifstream inputFile("config.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    string line;
    char delimiter = '=';

    string repo = "kubernetes/website";
    string path = "/content/en/docs/concepts/workloads/pods/_index.md";
    string full_path = repo + path;
    string token;

    while (std::getline(inputFile, line)) {
        size_t pos = line.find(delimiter);
        token = line.substr(pos+1, line.length());
        break;

        // KEEP ME FOR NOW
        // auto files = gitHubClient.list_files("kubernetes/kubernetes", "README.md").get();
        // for (const auto& file : files) {
        //     cout << file.name << " - " << file.type << endl;
        // }
    }

    inputFile.close();

    GitHubClient gitHubClient(token);
    auto response = gitHubClient.get_file_contents(repo, path);

    string contents = response.get();

    Cleaner cleaner;

    string cleaned_contents = cleaner.clean_string(contents);

    DocumentChunker chunker;

    vector<DocumentChunk> chunks = chunker.extract_chunks(cleaned_contents, full_path);

    cout << "Found " << chunks.size() << " chunks:" << endl;
    for (const auto& chunk : chunks) {
        cout << "\n--- Chunk " << chunk.chunk_index << " ---" << endl;
        cout << "Header: " << chunk.header << endl;
        cout << "Content preview: " << chunk.text.substr(0, 100) << "..." << endl;
        cout << "Content length: " << chunk.text.length() << endl;
    }

    return 0;
}