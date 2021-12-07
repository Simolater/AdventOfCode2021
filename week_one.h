#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <unordered_map>
#include <numeric>

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

    void day5(std::ifstream& file) {
        std::cout << "------------Day 05------------" << std::endl;

        using coord_t = uint32_t;

        // Stores the count with and without diagonals
        struct Cell {
            uint32_t countNonDiagonal;
            uint32_t count;

            Cell operator+= (const Cell& other) {
                countNonDiagonal += other.countNonDiagonal;
                count += other.count;
                return *this;
            }
        };

        struct pair_hash
        {
            std::size_t operator() (const std::pair<coord_t, coord_t> &pair) const {
                return std::hash<coord_t>()(pair.first) ^ std::hash<coord_t>()(pair.second);
            }
        };
        std::unordered_map<std::pair<coord_t , coord_t>, Cell, pair_hash> map;

        std::string input;
        while (std::getline(file, input)) {
            int x1, x2, y1, y2;
            std::stringstream inputStream(input);
            std::string value;
            if (!std::getline(inputStream, value, ',')) return;
            x1 = std::stoi(value);
            if (!std::getline(inputStream, value, ' ')) return;
            y1 = std::stoi(value);
            // Skip "-> "
            inputStream.ignore(3);
            if (!std::getline(inputStream, value, ',')) return;
            x2 = std::stoi(value);
            if (!std::getline(inputStream, value, ' ')) return;
            y2 = std::stoi(value);

            // Only increase non-diagonal count when it's a straight line
            Cell offset = {x1 == x2 || y1 == y2, 1};

            // Write initial pos
            { // in scope so I can use pos again later
                auto pos = std::make_pair(x1, y1);
                if (map.contains(pos)) {
                    map[pos] += offset;
                } else {
                    map[pos] = offset;
                }
            }
            // Write steps of the line
            while (x1 != x2 || y1 != y2) {
                auto xDiff = x2 - x1;
                if (xDiff < 0) {
                    --x1;
                } else if (xDiff > 0) {
                    ++x1;
                }
                auto yDiff = y2 - y1;
                if (yDiff < 0) {
                    --y1;
                } else if (yDiff > 0) {
                    ++y1;
                }
                auto pos = std::make_pair(x1, y1);
                if (map.contains(pos)) {
                    map[pos] += offset;
                } else {
                    map[pos] = offset;
                }
            }
        }

        uint64_t countNonDiagonal = 0, count = 0;
        for (auto value : map) {
            if (value.second.countNonDiagonal > 1) ++countNonDiagonal;
            if (value.second.count > 1) ++count;
        }

        std::cout << "Count: " << countNonDiagonal << " With diagonals: " << count << std::endl;
    }

    void day6_old(std::ifstream& file) {
        std::cout << "------------Day 06------------" << std::endl;

        constexpr uint64_t c_simulatedDays = 256;

        uint64_t state[9] = {0};

        // Parse state
        std::string input;
        while (std::getline(file, input, ',')) {
            ++state[std::stoi(input)];
        }

        uint64_t countAt80 = 0;
        for (auto i = 0; i < c_simulatedDays; ++i) {
            auto newFish = state[0];
            for (auto j = 0; j < 8; ++j) {
                state[j] = state[j + 1];
            }
            state[8] = newFish;
            state[6] += newFish;

            if (i == 79) countAt80 = std::accumulate(state, state + 9, countAt80);
        }
        uint64_t countAtEnd = 0;
        countAtEnd = std::accumulate(state, state + 9, countAtEnd);

        std::cout << "Amount of fish: " << std::endl;
        std::cout << "After 80 days: " << countAt80 << std::endl;
        std::cout << "After " << c_simulatedDays <<" days: " << countAtEnd << std::endl;
    }

    void day7(std::ifstream& file) {
        std::cout << "------------Day 07------------" << std::endl;

        std::vector<int64_t> crabs;

        std::string input;
        while (std::getline(file, input, ',')) {
            crabs.push_back(std::stoi(input));
        }

        int64_t lowestCost = std::numeric_limits<int64_t>::max(), at = 0;
        int64_t lowestCostB = std::numeric_limits<int64_t>::max(), atB = 0;
        for (auto i = 0; i < 1000; ++i) {
            // Calculate cost
            int64_t cost = 0, costB = 0;
            for (const auto& pos : crabs) {
                auto mov = std::abs(pos - i);
                cost += mov;
                costB += (mov * (mov + 1)) / 2;
            }
            if (cost < lowestCost) {
                lowestCost = cost;
                at = i;
            }
            if (costB < lowestCostB) {
                lowestCostB = costB;
                atB = i;
            }
        }

        std::cout << "At: " << at << " Cost: " << lowestCost << std::endl;
        std::cout << "At: " << atB << " Cost: " << lowestCostB << std::endl;
    }
}