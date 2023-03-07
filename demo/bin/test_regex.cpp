
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
    std::vector<int> rec_mark_vec;
    std::cout << "--> str_in = "<< str_in << std::endl;
    regex_seg(str_in,reg_abc,rec_str_vec,rec_mark_vec,debug);
    std::cout << "--> rec_str_vec.size() = "<< rec_str_vec.size() << std::endl;
    std::cout << "--> rec_mark_vec.size() = "<< rec_mark_vec.size() << std::endl;
    for (size_t i=0;i<rec_str_vec.size();i++){
        std::cout << i << ": " << rec_str_vec[i] << ":" << rec_mark_vec[i] << std::endl;
    }
    // std::cout << "--> num_in2= "<< num_in2 << std::endl;
    return 0;
}


