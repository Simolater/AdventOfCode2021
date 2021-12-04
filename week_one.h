#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>

namespace AoC {
    void day1(std::ifstream& file) {
        std::vector<int> values;
        std::string line;
        while(std::getline(file, line)) {
            values.push_back(std::stoi(line));
        }

        // Evaluate
        int basic_count = 0;
        int sliding_count = 0;

        { // Task 1
            for (int i = 1; i < values.size(); ++i) {
                if (values[i] > values[i - 1]) ++basic_count;
            }
        }
        { // Task 2
            for (int i = 3; i < values.size(); ++i) {
                if (values[i-3] < values[i]) ++sliding_count;
            }
        }

        std::cout << "------------Day 01------------" << std::endl;
        std::cout << "Increases: " << basic_count << " Sliding: " << sliding_count << std::endl << std::endl;
    }

    void day2(std::ifstream& file) {
        int depth = 0, pos = 0, aim = 0, aimed_depth = 0;
        std::string line;
        while(std::getline(file, line)) {
            auto command = line.substr(0, line.find_first_of(' '));
            auto value = std::stoi(line.substr(line.find_first_of(' ') + 1));
            if (command == "forward") {
                pos += value;
                aimed_depth += aim * value;
            } else if (command == "down") {
                depth += value;
                aim += value;
            } else if (command == "up") {
                depth -= value;
                aim -= value;
            }
        }
        std::cout << "------------Day 02------------" << std::endl;
        std::cout << "Depth: " << depth << " Pos: " << pos << " Depth*Pos: " << depth * pos << std::endl;
        std::cout << "With aim:" << std::endl;
        std::cout << "Depth: " << aimed_depth << " Pos: " << pos << " Depth*Pos: " << aimed_depth * pos << std::endl << std::endl;
    }

    void day3(std::ifstream& file) {

        const uint64_t bit_count = 12;
        uint64_t bits[bit_count] = {0};

        // needed for b
        std::vector<std::string> lines;

        std::string line;
        while(std::getline(file, line)) {
            for (uint64_t i = 0; i < bit_count; ++i) {
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
        uint64_t epsilon = ((1 << bit_count) - 1) - gamma;

        // Just playing with some lambda stuff for fun
        // This is unreadable ik
        auto filter_word_func = [](std::vector<std::string>& values, bool leastCommon = false) -> std::string {
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

        auto lines_copy(lines);
        auto oxygen = btoi(filter_word_func(lines_copy));
        auto co2 = btoi(filter_word_func(lines, true));

        std::cout << "------------Day 03------------" << std::endl;
        std::cout << "Gamma: " << gamma << " Epsilon: " << epsilon << " Gamma*Epsilon: " << gamma * epsilon << std::endl;
        std::cout << "Oxygen: " << oxygen << " CO2: " << co2 << " Oxygen*CO2: " << oxygen * co2 << std::endl;
    }
}