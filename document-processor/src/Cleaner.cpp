//
// Created by Mitchell on 9/21/2025.
//

#include "Cleaner.h"
#include <regex>
#include <string>
#include <iostream>

using std::regex;
using std::regex_replace;
using std::string;
using std::cout;
using std::endl;

Cleaner::Cleaner() {
}

std::string Cleaner::clean_string(std::string &contents) {
    regex shortcode_pattern(R"(\{\{<[^>]*>\}\}|\{\{</[^>]*>\}\})");
    string cleaned_string = regex_replace(contents, shortcode_pattern, "");

    regex link_pattern(R"(\[([^\]]+)\]\([^)]+\))");
    string replacement = "$1";

    cleaned_string = regex_replace(cleaned_string, link_pattern, replacement);

    cout << cleaned_string << endl;

    return cleaned_string;
}


