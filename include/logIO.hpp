#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <filesystem>
#include <rapidjson/document.h>

namespace insurance_log{
    namespace fs = std::filesystem;
    std::map<std::string, std::vector<std::tuple<int, int>>> read_log_file(const fs::path &log_file);
    std::tuple<
        std::string,
        std::vector<std::tuple<int,int>>
    > parsing_a_person(const rapidjson::Value &item);
}
