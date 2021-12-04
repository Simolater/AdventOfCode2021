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

        std::cout << "------------Day 03------------" << std::endl;
        std::cout << "Gamma: " << gamma << " Epsilon: " << epsilon << " Gamma*Epsilon: " << gamma * epsilon << std::endl;
        std::cout << "Oxygen: " << oxygen << " CO2: " << co2 << " Oxygen*CO2: " << oxygen * co2 << std::endl;
    }

    void day4(std::ifstream& file) {
        std::cout << "------------Day 04------------" << std::endl;
        constexpr int bingoSize = 5;
        struct Board {
            uint64_t numbers[25] = {0};
            bool marked[25] = {false};

            bool hasBingo() {
                // horizontal
                for (int i = 0; i < 25; i += 5) {
                    if (marked[i] && marked[i + 1] && marked[i + 2] && marked[i + 3] && marked[i + 4]) return true;
                }
                // vertical
                for (int i = 0; i < 5; ++i) {
                    if (marked[i] && marked[i + 5] && marked[i + 10] && marked[i + 15] && marked[i + 20]) return true;
                }
                return false;
            }

            uint64_t sumUnmarked() {
                uint64_t sum = 0;
                for (int i = 0; i < 25; ++i) {
                    if (!marked[i]) sum += numbers[i];
                }
                return sum;
            }
        };

        std::string drawnNumbersStr;
        if (!std::getline(file, drawnNumbersStr)) return;
        std::stringstream drawnNumbers(drawnNumbersStr);

        // Parse boards
        std::vector<Board> boards;
        std::string input;
        while (std::getline(file, input)) {
            if (!input.empty()) {
                std::cout << "invalid input format!" << std::endl;
                return;
            }
            Board board;
            for (auto i = 0; i < 5; ++i) {
                if (!std::getline(file, input)) {
                    std::cout << "invalid input format!" << std::endl;
                    return;
                }
                std::stringstream values(input);
                std::string number;
                for (auto j = 0; j < 5; ++j) {
                    do {
                        if (!std::getline(values, number, ' ')) {
                            std::cout << "invalid input format!" << std::endl;
                            return;
                        }
                    } while (number.empty());
                    board.numbers[i * 5 + j] = std::stoi(number);
                }
            }
            boards.push_back(board);
        }

        bool firstWin = true;
        uint64_t latestWinScore = 0;
        // Evaluate boards
        while (std::getline(drawnNumbers, input, ',')) {
            int value = std::stoi(input);
            // Mark boards
            for (auto board_it = boards.begin(); board_it != boards.end();) {
                // marks if board won in this round
                bool won = false;
                for (int i = 0; i < 25; ++i) {
                    if (board_it->numbers[i] == value) {
                        // Mark and check for bingo
                        board_it->marked[i] = true;
                        if (board_it->hasBingo()) {
                            latestWinScore = board_it->sumUnmarked() * value;
                            if (firstWin) {
                                std::cout << "First winning board has the final score: " << latestWinScore << std::endl;
                                firstWin = false;
                            }
                            won = true;
                            break;
                        }
                    }
                }
                if (won) {
                    board_it = boards.erase(board_it);
                } else {
                    ++board_it;
                }
            }
        }
        std::cout << "Last winning board has the final score: " << latestWinScore << std::endl;
    }
}