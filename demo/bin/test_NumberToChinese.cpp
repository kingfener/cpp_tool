
#include "utils_str.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc<2){
        std::cout << argv[0] <<" 1_num_in" << std::endl;
        return 0;
    }
    std::string val_str = argv[1];
    // unsigned long val_in = std::atol(argv[1]);
    unsigned long val_in = std::strtoul(val_str.c_str(),NULL,10);
    std::cout << "--> val_in = "<< val_in << std::endl;
    std::string res_str;
    NumberToChinese(val_in,res_str);
    std::cout << "--> val_in = "<< val_in << std::endl;
    std::cout << "--> res_str = "<< res_str << std::endl;
    return 0;
}


