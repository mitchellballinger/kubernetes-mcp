//
// Created by Mitchell on 9/21/2025.
//

#ifndef DOCUMENT_PROCESSOR_CLEANER_H
#define DOCUMENT_PROCESSOR_CLEANER_H
#include <string>


class Cleaner {
public:
    Cleaner();
    std::string clean_string(std::string &contents);
};


#endif //DOCUMENT_PROCESSOR_CLEANER_H