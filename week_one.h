#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
}