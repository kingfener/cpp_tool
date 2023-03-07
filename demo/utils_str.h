
#ifndef UTILS_STR.H
#define UTILS_STR.H

#include <iostream>
#include <regex>

void regex_seg(const std::string str_in,std::regex reg,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_mark_vec,int debug=0);
void str_to_vec(const std::string str_in,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_len_vec,int debug=0);

#endif // UTILS_STR.H
