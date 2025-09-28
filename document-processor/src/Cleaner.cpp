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
    // Handle {{< >}} and {{</ >}} shortcodes
    regex shortcode_pattern(R"(\{\{<[^>]*>\}\}|\{\{</[^>]*>\}\})");
    string cleaned_string = regex_replace(contents, shortcode_pattern, "");

    // Handle {{% %}} shortcodes
    regex percent_shortcode_pattern(R"(\{\{%[^%]*%\}\})");
    cleaned_string = regex_replace(cleaned_string, percent_shortcode_pattern, "");

    // Clean markdown links
    regex link_pattern(R"(\[([^\]]+)\]\([^)]+\))");
    string replacement = "$1";
    cleaned_string = regex_replace(cleaned_string, link_pattern, replacement);

    // Remove header anchor tags like {#pod-security}
    regex anchor_pattern(R"(\{#[^}]*\})");
    cleaned_string = regex_replace(cleaned_string, anchor_pattern, "");

    regex frontmatter_pattern(R"(^---[\s\S]*?---\n)");
    cleaned_string = regex_replace(cleaned_string, frontmatter_pattern, "");

    return cleaned_string;
}


