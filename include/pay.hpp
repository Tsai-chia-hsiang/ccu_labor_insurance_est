#pragma once
#include <vector>
#include <tuple>
#include <iostream>
#include <array>
#include <string>
#include "insurance_table.hpp"


std::string format_indent_str(const std::string& s, int len);

struct pay{

    public:    
        pay(
            int hourly_rate, float supp_rate,
            const std::vector<std::tuple<int, int>>& working_seqs,
            const std::map<std::string, std::vector<int>>& table
        );
        pay() noexcept: wage_(0), total_pay_(0), employer_support_(0),
        employer_insurance_(0), employer_retirement_(0),
        employer_total_extra_(0) {}

        
        
        friend std::ostream& operator<<(std::ostream& os, const pay& p);
        static const std::string column; 

        [[nodiscard]] int wage() const noexcept { return wage_; }
        [[nodiscard]] int total_pay() const noexcept { return total_pay_; }
        [[nodiscard]] int employer_support() const noexcept { return employer_support_; }
        [[nodiscard]] int employer_insurance() const noexcept { return employer_insurance_; }
        [[nodiscard]] int employer_retirement() const noexcept { return employer_retirement_; }
        [[nodiscard]] int employer_total_extra() const noexcept { return employer_total_extra_; }

        // For vectors: const& for read-only, non-const& if you need mutation
        [[nodiscard]] const std::vector<int>& seq_ins() const noexcept { return seq_ins_; }
        [[nodiscard]] const std::vector<int>& seq_retirement() const noexcept { return seq_retirement_; }
        
        pay& operator+=(const pay& rhs) noexcept;
        friend pay operator+(pay lhs, const pay& rhs) noexcept;
    
        std::string payment_json_string() const{
            return std::string(
                "{\"wage\":"+std::to_string(wage_)+","
                "\"employer_support\":" +std::to_string(employer_support_)+","+
                "\"employer_insurance\":"+ std::to_string(employer_insurance_)+","+
                "\"employer_retirement\":"+ std::to_string(employer_retirement_)+","+
                "\"employer_total_extra\":"+std::to_string(employer_total_extra_)+","+
                "\"total_pay\":"+std::to_string(total_pay_) + "}"
            );
        }
        

    protected:
        int wage_;
        int total_pay_;
        int employer_support_;
        int employer_insurance_;
        int employer_retirement_;
        int employer_total_extra_;
        std::vector<int> seq_ins_, seq_retirement_;

};
