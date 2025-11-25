#pragma once

#include <iostream>
#include <fstream>
#include <format>

#include "count_bytes.hpp"

size_t count_bytes::execute(const std::string& fileName) {
    size_t op = 0;
    try {
        std::ifstream file;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        file.open(fileName, std::ios::binary);
        if (!file.is_open()) {
            std::cout << std::format("unable to open file \"{}\".", fileName) << std::endl;
        }

        file.seekg(0, std::ios::end);
        op = file.tellg();
        file.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return op;
}
