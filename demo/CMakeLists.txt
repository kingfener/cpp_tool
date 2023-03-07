

cmake_minimum_required (VERSION 3.5)
project(demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")
include_directories(
    ./
    ../
)
set (src
    ./utils_str.cpp
)
# Add an executable
add_executable(demo demo.cpp)

add_executable(test_regex bin/test_regex.cpp ${src})
add_executable(test_str_to_vec bin/test_str_to_vec.cpp ${src})
add_executable(test_digit_to_chinese bin/test_digit_to_chinese.cpp ${src})
add_executable(test_NumberToChinese bin/test_NumberToChinese.cpp ${src})


