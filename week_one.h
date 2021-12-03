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
        // This has to have a cleaner solution
        const uint64_t bit_count = 12;
        uint64_t bits[bit_count * 2] = {0};

        // needed for b
        std::vector<std::string> lines;

        std::string line;
        while(std::getline(file, line)) {
            for (uint64_t i = 0; i < bit_count; ++i) {
                if (line.at(i) == '0') {
                    ++bits[i];
                } else {
                    ++bits[i + bit_count];
                }
            }
            lines.push_back(line);
        }

        uint64_t gamma = 0;
        for (uint64_t i = 0; i < bit_count; ++i) {
            gamma <<= 1;
            if (bits[i] > bits[i + bit_count]) {
                ++gamma;
            }
        }

        // Epsilon is just inverted gamma
        uint64_t epsilon = ((1 << bit_count) - 1) - gamma;


        std::string i_oxygen, i_co2, oxygen, co2;
        // Additional passes for b
        for (int i = 0; i < bit_count; ++i) {
            if (bits[i] <= bits[i + bit_count]) {
                i_oxygen.append("1");
                i_co2.append("0");
            } else {
                i_oxygen.append("0");
                i_co2.append("1");
            }
            if (std::count_if(lines.cbegin(), lines.cend(), [&i_co2](const std::string& s) {return s.starts_with(i_co2);}) == 1) {
                co2 = std::find_if(lines.cbegin(), lines.cend(), [&i_co2](const std::string& s) {return s.starts_with(i_co2);})[0];
            }
            if (std::count_if(lines.cbegin(), lines.cend(), [&i_oxygen](const std::string& s) {return s.starts_with(i_oxygen);}) == 1) {
                oxygen = std::find_if(lines.cbegin(), lines.cend(), [&i_oxygen](const std::string& s) {return s.starts_with(i_oxygen);})[0];
            }
        }

        std::cout << "------------Day 03------------" << std::endl;
        std::cout << "Gamma: " << gamma << " Epsilon: " << epsilon << " Gamma*Epsilon: " << gamma * epsilon << std::endl;

        std::cout << "Oxygen: " << oxygen << " Co2: " << co2 << std::endl;
        for (auto bit : bits) {
            std::cout << bit << " ";
        }
    }
}