//
// Created by Mitchell on 9/15/2025.
//

#include "GitHubClient.h"
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <cpprest/json.h>
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>
#include <algorithm>

using std::string;
using std::vector;
using pplx::task;
using std::remove;
using std::cout;
using std::endl;


GitHubClient::GitHubClient(const string &token)
    : apiToken(token),
      client_(web::http::client::http_client(U("https://api.github.com"))) {

}

task<string> GitHubClient::get_file_contents(const string& repo, const string& path) {
    string uri_string = "/repos/" + repo + "/contents/" + path;
    web::uri_builder builder(utility::conversions::to_string_t(uri_string));

    return client_.request(web::http::methods::GET, builder.to_string())
        .then([](web::http::http_response response) {
            return response.extract_utf8string();
        })
        .then([](string json_body) {
            nlohmann::json parsed = nlohmann::json::parse(json_body);
            string base64_content = parsed["content"];

            auto result = std::ranges::remove(base64_content, '\n');
            base64_content.erase(result.begin(), result.end());

            std::vector<unsigned char> decoded_data = utility::conversions::from_base64(utility::conversions::to_string_t(base64_content));

            return string(decoded_data.begin(), decoded_data.end());
        });
}

task<vector<GitHubFile>>GitHubClient::list_files(const string& repo, const string& path) {
    string uri_string = "/repos/" + repo + "/contents/README.md";
    web::uri_builder builder(utility::conversions::to_string_t(uri_string));

    return client_.request(web::http::methods::GET, builder.to_string())
        .then([](web::http::http_response response) {
            return response.extract_utf8string();
        })
        .then([](string json_body) {
            nlohmann::json parsed = nlohmann::json::parse(json_body);
            vector<GitHubFile> files;

            if (parsed.is_array()) {
                for (const auto& item : parsed) {
                    GitHubFile file;
                    file.name = item["name"];
                    file.path = item["path"];
                    file.type = item["type"];
                    if (item.contains("download_url") && !item["download_url"].is_null()) {
                        file.download_url = item["download_url"];
                    }
                    files.push_back(file);
                }
            }
            else {
                GitHubFile file;
                file.name = parsed["name"];
                file.path = parsed["path"];
                file.type = parsed["type"];
                if (parsed.contains("download_url") && !parsed["download_url"].is_null()) {
                        file.download_url = parsed["download_url"];
                    }
                    files.push_back(file);
            }

            return files;
        });
}
