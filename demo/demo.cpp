#include <iostream>

int main(int argc, char *argv[])
{
    if (argc<2){
        std::cout<< argv[0] << " 1_str_in 2_num_in" << std::endl;
        return 0;
    }
    std::string str_in = argv[1];
    int num_in = std::atoi(argv[2]);
    // int num_in2 = std::stoi(argv[2]);
    std::cout << "--> str_in = "<< str_in << std::endl;
    std::cout << "--> num_in = "<< num_in << std::endl;
    // std::cout << "--> num_in2= "<< num_in2 << std::endl;

    return 0;
}
