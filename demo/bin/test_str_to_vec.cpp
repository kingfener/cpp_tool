
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
    str_to_vec(str_in,rec_str_vec,rec_len_vec,debug);
    std::cout << "--> rec_str_vec.size() = "<< rec_str_vec.size() << std::endl;
    for (size_t i=0;i<rec_str_vec.size();i++){
        std::cout << i << ": " << rec_str_vec[i] << " len= "<< rec_len_vec[i] << std::endl;
    }
    return 0;
}


