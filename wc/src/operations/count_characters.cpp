#pragma once

#include "count_characters.hpp"

#include <iostream>
#include <fstream>
#include <format>
#include <string>

#include "rang.hpp"

size_t count_characters::execute(const std::string& fileName) {
    size_t chars = 0;
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << std::format("Unable to open file \"{}\"", fileName);
        return -1;
    }

    setlocale(LC_ALL, "");
    std::cout << rang::fg::red << "LC_ALL: " << rang::fg::magenta << setlocale(LC_ALL, NULL) 
        << rang::style::reset << std::endl;

    // not all bytes from utf-8 fit in signed character (128), so using unsigned char
    unsigned char c;
    while (file.read(reinterpret_cast<char*>(&c), 1)) {
        if ((c & 0xC0) != 0x80) {
            chars++;
        }
    }
    
    return chars;
}