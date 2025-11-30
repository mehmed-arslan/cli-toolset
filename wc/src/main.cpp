#pragma once

#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <io.h>

#include "operation.hpp"
#include "count_bytes.hpp"
#include "count_lines.hpp"
#include "count_words.hpp"
#include "count_characters.hpp"

int main(int argc, char *argv[])
{
  std::ifstream file;
  std::string fileName;

  // setup commands for strategy 
  std::unordered_map<std::string, std::unique_ptr<operation>> commands;
  commands["-c"] = std::make_unique<count_bytes>();
  commands["-l"] = std::make_unique<count_lines>();
  commands["-w"] = std::make_unique<count_words>();
  commands["-m"] = std::make_unique<count_characters>();

  std::vector<std::string> args(argv + 1, argv + argc);
  
  // get input streams
  std::istream* input;
  std::stringstream buffer;
  bool isPipedInput = !_isatty(_fileno(stdin));
  if (isPipedInput) {
    buffer << std::cin.rdbuf();
    input = &buffer;
  } else {
    // TODO: update dataPath to current dir where .exe is run
    std::string dataPath = "../../data/";
    std::string completeFilePath;
    if (!args.empty() && args.back()[0] != '-') {
      fileName = args.back();
      args.pop_back();
      completeFilePath = dataPath + fileName;
      file.open(completeFilePath, std::ios::binary);

      if (!file.is_open()) {
        std::cerr << "Error opening file: " << completeFilePath << "\n";
        return 1;
      }

      input = &file;
    } else {
      std::cerr << "No input file specified!\n";
      return 1;
    }
  }


  // set operations to execute
  std::vector<operation *> flags;
  for (const std::string &flag : args)
  {
    if (commands.find(flag) != commands.end())
    {
      flags.emplace_back(commands[flag].get());
    }
  }
  // If no flags are provided, return -c, -l, -w
  if (flags.empty())
  {
    flags.emplace_back(commands["-c"].get());
    flags.emplace_back(commands["-l"].get());
    flags.emplace_back(commands["-w"].get());
  }

  // execute operations
  for (operation* op: flags) {
    // rewind
    input->clear();
    input->seekg(0, std::ios::beg);

    std::cout << op -> execute(*input) << " ";
  }
  if (!isPipedInput) {
    std::cout << fileName << std::endl;
  }

  return 0;
}