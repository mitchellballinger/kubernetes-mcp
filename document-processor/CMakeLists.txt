cmake_minimum_required(VERSION 4.0)
project(document_processor)

set(CMAKE_CXX_STANDARD 20)

find_package(cpprestsdk REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

add_executable(document_processor src/main.cpp
        src/api/GitHubClient.cpp
        src/api/GitHubClient.h
        src/Cleaner.cpp
        src/Cleaner.h
        src/DocumentChunker.cpp
        src/DocumentChunker.h)

target_link_libraries(document_processor
        PRIVATE
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)