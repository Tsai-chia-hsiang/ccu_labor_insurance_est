#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <map>
#include <rapidjson/document.h>
#include "logIO.hpp"

namespace insurance_log{
namespace fs = std::filesystem;

std::tuple<
    std::string,
    std::vector<std::tuple<int,int>>
> parsing_a_person(const rapidjson::Value &item){
    std::string name;
    name = item["name"].GetString();
    std::vector<std::tuple<int, int>> seq;
    for (const auto& elem : item["seq"].GetArray()){
        seq.emplace_back(elem[0].GetInt(), elem[1].GetInt());
    }  
    return std::tuple{name, seq};
}

std::map<std::string, std::vector<std::tuple<int, int>>>read_log_file(const fs::path &log_file){
    
    if (! fs::exists(log_file)){
        std::cerr << "No such a file " << 
            log_file.generic_string() <<  
            "\n";
        throw std::runtime_error("file not found"); 
    }
    
    std::ifstream file(log_file);
    if (!file.is_open()){
        std::cerr << "the file "  << log_file.generic_string() << 
        "could not be opened\n";
        throw std::runtime_error ("file can't be opened"); 
    }

    std::cout << "insurance log: " << log_file << "\n"; 
    std::map<std::string, std::vector<std::tuple<int, int>>> log = {};
    std::stringstream buffer;
    buffer << file.rdbuf();  // read entire file
    std::string jsonStr = buffer.str();

    // 2. Parse JSON
    rapidjson::Document doc;
    if (doc.Parse(jsonStr.c_str()).HasParseError()) {
        file.close();
        throw std::runtime_error("Error parsing JSON, return empty map\n");
    }

    auto handle = [&](const rapidjson::Value& item) {
        if (!item.IsObject()) return;           // guard, just in case
        auto [name, seq] = parsing_a_person(item);
        log.emplace(name, std::move(seq));
    };

    if (doc.IsArray()) {
        for (const auto& item : doc.GetArray()) {
            handle(item);
        }
    } else if (doc.IsObject()) {
        handle(doc);
    }

    file.close();
    return log;
}
}
