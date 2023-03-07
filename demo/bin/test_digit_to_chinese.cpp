
#include "utils_str.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc<3){
        std::cout << argv[0] <<" 1_str_in 2_num_in" << std::endl;
        return 0;
    }
    std::string str_in = argv[1];
    int debug = std::atoi(argv[2]);

    std::regex reg_abc("[a-zA-Z ]+");
    std::regex reg_ssml("<speak>.*?</speak>");
    std::vector<std::string> rec_str_vec;
    std::vector<int> rec_len_vec;
    std::cout << "--> str_in = "<< str_in << std::endl;
    std::string res = digit_to_chinese(str_in,debug);
    std::cout << "--> debug = "<< debug << std::endl;
    std::cout << "--> res = "<< res << std::endl;
    return 0;
}


