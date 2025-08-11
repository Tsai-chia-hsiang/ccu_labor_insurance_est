#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include "insurance_table.hpp"

namespace insurance{

strvec read_header_row(const std::string &l, char delimiter){
    strvec tokens;
    std::stringstream ss(l);
    std::string token;
    while (std::getline(ss, token, delimiter)){
        tokens.emplace_back(token);
    }
    return tokens;
}

std::vector<int> read_value_row(const std::string &l, char delimiter, int dim){
    
    std::vector<int> tokens;
    tokens.reserve(dim);

    std::stringstream ss(l);
    std::string token;
    
    while (std::getline(ss, token, delimiter)){
        tokens.emplace_back(std::stoi(token));
    }
    return tokens; 
}

std::map<std::string, std::vector<int>> read_table(const fs::path &table_file){
    
    std::map<std::string, std::vector<int>> table;
    
    if (! fs::exists(table_file)){
        std::cerr << "No such a file " << 
            table_file.generic_string() <<  
            "\n";
        throw std::runtime_error("file not found"); 
    }
    
    std::ifstream file(table_file);
    if (!file.is_open()){
        std::cerr << "the file "  << table_file.generic_string() << 
        "could not be opened\n";
        throw std::runtime_error ("file can't be opened"); 
    }

    std::string csvline;
    //read header
    if (!std::getline(file, csvline)){
        std::cerr << "empty file\n" ; 
        file.close();
        return table; 
    }
    

    strvec header = read_header_row(csvline, ','); 
    std::vector<std::vector<int>*> cols;
    cols.reserve(header.size());
    for (std::string &key : header){
        auto& vec = table.emplace(key, std::vector<int>{}).first->second;
        cols.push_back(&vec);
    }
   
    while(std::getline(file, csvline)){

        std::vector<int> row = read_value_row(csvline, ',', header.size());

        for (size_t i = 0; i < row.size(); ++i){
            cols[i]->push_back(row[i]);       
        }
            
    } 
    std::cout<< "Table readed from " << table_file << " is ready. \n"; 
    file.close();
    return table;
}


}