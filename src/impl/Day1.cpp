//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"

constexpr size_t c_day = 1;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t values;
    for(std::string line; std::getline(input, line);) {
        values.push_back(std::stoi(line));
    }
    return values;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    int count{0};
    for (auto i = 1; i < input.size(); ++i) {
        if (input[i] > input[i - 1]) ++count;
    }
    return count;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    int count{0};
    for (int i = 3; i < input.size(); ++i) {
        if (input[i-3] < input[i]) ++count;
    }
    return count;
}
