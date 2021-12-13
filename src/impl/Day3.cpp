//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"

constexpr size_t c_day = 3;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t values;
    for (std::string line; std::getline(input, line);) {
        if (line.ends_with('\r')) {
            line = line.erase(line.size() - 1);
        }
        values.push_back(line);
    }
    return values;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {

    uint64_t bit_count = input[0].length();
    std::vector<uint64_t> bits;
    bits.resize(bit_count, 0);

    for (const auto& value : input) {
        for (uint64_t i = 0; i < bit_count; ++i) {
            if (value.at(i) == '0') {
                ++bits[i];
            }
        }
    }
    const auto value_count = input.size() / 2;

    uint64_t gamma{0};
    for (auto bit : bits) {
        gamma <<= 1;
        if (bit >= value_count) {
            ++gamma;
        }
    }

    // Epsilon is just inverted gamma
    uint64_t epsilon = ((1 << bit_count) - 1) - gamma;

    return static_cast<int>(gamma) * static_cast<int>(epsilon);
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    // Just playing with some lambda stuff for fun

    uint64_t bit_count = input[0].length();
    // This is unreadable ik
    auto filterWordFunc = [bit_count](std::vector<std::string>& values, bool leastCommon = false) -> std::string {
        for (int i = 0; i < bit_count; ++i) {
            uint64_t zero_count = std::count_if(values.begin(), values.end(), [i](const std::string& value) {return value.at(i) == '0';});
            char filter = values.size() - zero_count >= zero_count ? '1' : '0';
            values.erase(std::remove_if(values.begin(), values.end(), [i, leastCommon, filter](const std::string& value) {
                return leastCommon ^ (value.at(i) != filter);
            }), values.end());
            if (values.size() == 1) return values[0];
        }
        return "0";
    };

    // This lambda converts binary string into unsigned int
    auto btoi = [](const std::string& bin) -> uint64_t {
        uint64_t val = 0;
        for (const char &c : bin) {
            val <<= 1;
            if (c == '1') ++val;
        }
        return val;
    };

    auto linesCopy(input);
    auto oxygen = btoi(filterWordFunc(linesCopy));
    auto linesCopy2(input);
    auto co2 = btoi(filterWordFunc(linesCopy2, true));

    return static_cast<int>(oxygen) * static_cast<int>(co2);
}
