#include <iostream>
#include <array>
#include <algorithm>
#include "Matrix.h"

namespace AoC {

    void day3(std::ifstream& file) {

        constexpr uint64_t c_bit_count = 12;
        uint64_t bits[c_bit_count] = {0};

        // needed for b
        std::vector<std::string> lines;

        std::string line;
        while(std::getline(file, line)) {
            for (uint64_t i = 0; i < c_bit_count; ++i) {
                if (line.at(i) == '0') {
                    ++bits[i];
                }
            }
            lines.push_back(line);
        }
        const auto value_count = lines.size() / 2;

        uint64_t gamma = 0;
        for (auto bit : bits) {
            gamma <<= 1;
            if (bit >= value_count) {
                ++gamma;
            }
        }

        // Epsilon is just inverted gamma
        uint64_t epsilon = ((1 << c_bit_count) - 1) - gamma;

        // Just playing with some lambda stuff for fun
        // This is unreadable ik
        auto filterWordFunc = [](std::vector<std::string>& values, bool leastCommon = false) -> std::string {
            for (int i = 0; i < c_bit_count; ++i) {
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

        auto linesCopy(lines);
        auto oxygen = btoi(filterWordFunc(linesCopy));
        auto co2 = btoi(filterWordFunc(lines, true));

        std::cout << "Gamma: " << gamma << " Epsilon: " << epsilon << " Gamma*Epsilon: " << gamma * epsilon << std::endl;
        std::cout << "Oxygen: " << oxygen << " CO2: " << co2 << " Oxygen*CO2: " << oxygen * co2 << std::endl;
    }
}