//
// Created by Mitchell on 9/15/2025.
//

#ifndef DOCUMENT_PROCESSOR_GITHUB_CLIENT_H
#define DOCUMENT_PROCESSOR_GITHUB_CLIENT_H
#include <string>
#include <vector>
#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>
#include <cpprest/uri_builder.h>

struct GitHubFile {
    std::string name;
    std::string path;
    std::string type;
    std::string download_url;
};

class GitHubClient {
    std::string apiToken;
    web::http::client::http_client client_;

    public:
        GitHubClient(const std::string& token);

        pplx::task<std::string> get_file_contents(const std::string& repo, const std::string& path);
        pplx::task<std::vector<GitHubFile>> list_files(const std::string& repo, const std::string& path);

};


#endif //DOCUMENT_PROCESSOR_GITHUB_CLIENT_H