#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <array>
#include "insurance_table.hpp"
#include "pay.hpp"

std::string format_indent_str(const std::string& s, int len){
    int right_offset = (len - s.size()) >> 1;
    int left_offset = len - (int)s.size() - right_offset;
    left_offset = (left_offset > 0) ? left_offset : 0;
    return std::string(left_offset, ' ') + s + std::string(right_offset, ' '); 
}



pay::pay(
    int hourly_rate, 
    float supp_rate, 
    const std::vector<std::tuple<int, int>>& working_seqs,
    const std::map<std::string, std::vector<int>>& table
){
    
    wage_ = 0;

    int day_wage, seq_wage, level_index=0;
    float work_day_rate;
    
    // std::vector<int>::const_iterator wage_level_end = table.at("wage").end();
    
    seq_ins_.resize(working_seqs.size(), 0);
    seq_retirement_.resize(working_seqs.size(), 0);

    for (size_t i = 0; i < working_seqs.size(); ++i){

        auto &[hour, day] = working_seqs[i]; 
        day_wage = hourly_rate*hour;
        wage_ += day_wage*day;

        seq_wage = day_wage * 30;
        work_day_rate = (float)day/30.0;

        std::vector<int>::const_iterator lb = std::lower_bound(table.at("wage").begin(), table.at("wage").end(), seq_wage);
        level_index = std::distance(table.at("wage").begin(), lb);

        seq_ins_[i] = round(table.at("employer_ins")[level_index]*work_day_rate);
        seq_retirement_[i] = round(table.at("employer_retirement")[level_index]*work_day_rate);

    }

    employer_support_ = round(wage_*supp_rate);
    employer_insurance_ = std::accumulate(seq_ins_.begin(), seq_ins_.end(), 0);
    employer_retirement_ = std::accumulate(seq_retirement_.begin(),seq_retirement_.end(),0);
    
    employer_total_extra_ = employer_support_ + employer_insurance_ + employer_retirement_; 
    total_pay_ = wage_ + employer_total_extra_;
}

const std::string pay::column = "|  wage + (  sup  +  ins  + retir = extra ) = total |";

std::ostream& operator<<(std::ostream& os, const pay& p){
    // |  wage  + ( emp.sup + emp.ins + emp.retire = emp.extra ) = total |
    return os 
    <<"|" << format_indent_str(std::to_string(p.wage_), 7) << "+ ("
    << format_indent_str(std::to_string(p.employer_support_), 7) << "+"
    << format_indent_str(std::to_string(p.employer_insurance_), 7) << "+"
    << format_indent_str(std::to_string(p.employer_retirement_), 7) << "="
    << format_indent_str(std::to_string(p.employer_total_extra_), 7) << ")"
    << " =" << format_indent_str(std::to_string(p.total_pay_), 7) << "|";
}      

pay& pay::operator+=(const pay& rhs) noexcept {
    wage_                 += rhs.wage_;
    total_pay_            += rhs.total_pay_;
    employer_support_     += rhs.employer_support_;
    employer_insurance_   += rhs.employer_insurance_;
    employer_retirement_  += rhs.employer_retirement_;
    employer_total_extra_ += rhs.employer_total_extra_;
    // seq_*: choose policy. Often we don't sum vectors here.
    return *this;
}
pay operator+(pay lhs, const pay& rhs) noexcept {
    lhs += rhs;
    return lhs;
}