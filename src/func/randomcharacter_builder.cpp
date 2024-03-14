#include <iostream>
#include <random>
#include <string>
#include "../head/randomcharacter_builder.h"

std::string genRandomChar(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);

    std::string result;
    for (int i=0; i<length; ++i) {
        char randomChar = 'a' + dis(gen);
        result += randomChar;
    }
    return result;
}