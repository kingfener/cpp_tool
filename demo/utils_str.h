
#ifndef UTILS_STR_H_
#define UTILS_STR_H_

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

void regex_seg(const std::string& str_in,std::regex reg,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_mark_vec,int debug=0);
void str_to_vec(const std::string& str_in,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_len_vec,int debug=0);
std::string digit_to_chinese(const std::string& str_in,int is_tele_num);
void NumberToChinese(unsigned long num, std::string& chnStr);
void SectionToChinese(unsigned long section, std::string& chnStr);
#endif // UTILS_STR_H_
