#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <numeric>
#include <map>
#include <vector>
#include "insurance_table.hpp"
#include "pay.hpp"
#include "logIO.hpp"

namespace fs = std::filesystem;
using strvec = std::vector<std::string>;
inline const fs::path filedir = fs::path(".");
inline const fs::path insuran_table_root = fs::path("insurance_tables");
const int hourly_rate=190;
const float supp_rate = 0.0211;

template<typename T>
void print_vector(const std::vector<T>& vec, bool chline){
    for (const auto &v: vec){
        std::cout << v << " ";
    }
    if (chline){
        std::cout << "\n";
    }
}

int main(int arg, char **argv){
    
    system("chcp 65001");
    fs::path insurance_talbe = insuran_table_root/"2025.csv";
    assert (arg > 1);
    fs::path log_file(argv[1]);
    

    std::map<std::string, std::vector<int>> table = insurance::read_table(insurance_talbe);
    std::map<
        std::string, std::vector<std::tuple<int, int>>
    > seqs = insurance_log::read_log_file(log_file);
    
    std::string splitline(pay::column.size() + 7, '-');

    std::cout << '\n' << splitline << '\n' << "| name " 
    << pay::column << "\n" << splitline << "\n";

    std::map<std::string, pay> seqs_pay;
    for (auto &[name, seq] : seqs){
        std::cout<< "|" << format_indent_str(name, 6);
        pay a_pay(hourly_rate, supp_rate, seq, table);
        seqs_pay.emplace(name, std::move(a_pay));
        std::cout << seqs_pay.at(name) << '\n';
    }
    std::cout << splitline << '\n';
    pay total = std::accumulate(
        seqs_pay.begin(), seqs_pay.end(), pay{},
        [](pay acc, const auto& kv){ 
            return acc += kv.second;
        }
    );
    std::cout << "|" << format_indent_str("Accumu", 6)
    << total << '\n' << splitline << "\n\n";
    
    return 0;
}