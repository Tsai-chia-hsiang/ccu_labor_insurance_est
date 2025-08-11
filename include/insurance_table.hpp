#pragma once
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <variant>

namespace insurance {
    namespace fs = std::filesystem;
    using strvec = std::vector<std::string>;
    strvec read_header_row(const std::string &l, char delimiter);
    std::vector<int> read_value_row(const std::string &l, char delimiter, int dim);
    std::map<std::string, std::vector<int>> read_table(const fs::path &table_file);
}