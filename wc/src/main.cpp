#pragma once

#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <unordered_map>
#include <memory>

#include "operation.hpp"
#include "count_bytes.hpp"
#include "count_lines.hpp"
#include "count_words.hpp"
#include "count_characters.hpp"

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, std::unique_ptr<operation>> commands;
    commands["-c"] = std::make_unique<count_bytes>();
    commands["-l"] = std::make_unique<count_lines>();
    commands["-w"] = std::make_unique<count_words>();
    commands["-m"] = std::make_unique<count_characters>();
 
    std::string dataPath = "../../data/";
    vector<std::string> args(argv + 1, argv + argc);
    std::string fileName, completeFilePath;
    if (!args.empty() && args.back()[0] != '-') {
      fileName = args.back();
      args.pop_back();
    }

    vector<operation*> flags;
    for (const std::string& flag: args) {
      if (commands.find(flag) != commands.end()) {
        flags.emplace_back(commands[flag].get()); 
      }
    }
    // If no flags are provided, return -c, -l, -w
    if (flags.empty()) {
      flags.emplace_back(commands["-c"].get());
      flags.emplace_back(commands["-l"].get());
      flags.emplace_back(commands["-w"].get());
    }
    
    // TODO
    // get input from pipe
    // need to use istream
    // use istream instead on ifstream in derived operations?


    // std::string dataPath = "../../data/";
    // std::string fileName, completeFilePath;
    // int op = 0;
    // if (argc > 0) {
    //     fileName = argv[2];
    //     completeFilePath = dataPath + fileName;
    //     std::vector<std::string> args(argv + 1, argv + argc);
       
    //     for (const auto& arg: args) {
    //         if (arg == "-c") {
    //             op = count_bytes(completeFilePath);
    //         }
    //         else if (arg == "-l") {
    //             op = get_lines(completeFilePath);
    //         } 
    //         else if (arg == "-w") {
    //             op = get_words(completeFilePath);
    //         }
    //         else if (arg == "-m") {
    //             op = get_characters(completeFilePath);
    //         }
    //     }
    // }

    // std::cout << std::format("{} {}", op, fileName) << std::endl;
    return 0;
}
