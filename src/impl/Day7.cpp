//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"

constexpr size_t c_day = 7;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string value; std::getline(input, value, ',');) {
        output.push_back(std::stoi(value));
    }
    return output;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    day_result_t lowestCost = std::numeric_limits<day_result_t>::max();
    for (auto i = 0; i < 1000; ++i) {
        // Calculate cost
        int64_t cost = 0;
        for (const auto& pos : input) {
            auto mov = std::abs(pos - i);
            cost += mov;
        }
        if (cost < lowestCost) {
            lowestCost = cost;
        }
    }
    return lowestCost;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    day_result_t lowestCost = std::numeric_limits<day_result_t>::max();
    for (auto i = 0; i < 1000; ++i) {
        // Calculate cost
        int64_t cost = 0;
        for (const auto& pos : input) {
            auto mov = std::abs(pos - i);
            cost += (mov * (mov + 1)) / 2;
        }
        if (cost < lowestCost) {
            lowestCost = cost;
        }
    }
    return lowestCost;
}
