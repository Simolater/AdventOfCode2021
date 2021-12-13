//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"

constexpr size_t c_day = 2;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    std::vector<std::pair<int, int>> values;
    for (std::string line; std::getline(input, line);) {
        auto command = line.substr(0, line.find_first_of(' '));
        auto value = std::stoi(line.substr(line.find_first_of(' ') + 1));
        values.emplace_back(command[0], value);
    }
    return values;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    int pos{0}, depth{0};
    for (const auto& entry : input) {
        switch (entry.first) {
            case 'f':
                pos += entry.second;
                break;
            case 'd':
                depth += entry.second;
                break;
            case 'u':
                depth -= entry.second;
                break;
        }
    }
    return pos * depth;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    int pos{0}, depth{0}, aim{0};
    for (const auto& entry : input) {
        switch (entry.first) {
            case 'f':
                pos += entry.second;
                depth += aim * entry.second;
                break;
            case 'd':
                aim += entry.second;
                break;
            case 'u':
                aim -= entry.second;
                break;
        }
    }
    return pos * depth;
}
