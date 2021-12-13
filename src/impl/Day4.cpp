//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <set>

constexpr size_t c_day = 4;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;

    std::string drawnNumbersStr;
    if (!std::getline(input, drawnNumbersStr)) return output;
    std::stringstream drawnNumbers(drawnNumbersStr);
    for (std::string number; std::getline(drawnNumbers, number, ',');) {
        output.values.push_back(std::stoi(number));
    }
    // Parse boards
    for (std::string line; std::getline(input, line);) {
        decltype(output.boards)::value_type board;
        for (auto i = 0; i < 5; ++i) {
            if (!std::getline(input, line)) {
                std::cout << "invalid input format!" << std::endl;
                return output;
            }
            std::stringstream values{line};
            std::string number;
            for (auto j = 0; j < 5; ++j) {
                do {
                    if (!std::getline(values, number, ' ')) {
                        std::cout << "invalid input format!" << std::endl;
                        return output;
                    }
                } while (number.empty());
                board(i, j) = std::stoi(number);
            }
        }
        output.boards.push_back(board);
    }
    return output;
}

bool hasBingo(const AoC::Matrix<5, 5, bool>& marked, int x, int y) {
    if (marked(y, 0) && marked(y, 1) && marked(y, 2) && marked(y, 3) && marked(y, 4)) return true;
    if (marked(0, x) && marked(1, x) && marked(2, x) && marked(3, x) && marked(4, x)) return true;
    return false;
}

int sumUnmarked(const AoC::Matrix<5, 5, int>& board, const AoC::Matrix<5, 5, bool>& marked) {
    int sum{0};
    for (auto y = 0; y < 5; ++y) {
        for (auto x = 0; x < 5; ++x) {
            if (!marked(y, x)) {
                sum += board(y, x);
            }
        }
    }
    return sum;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    std::vector<Matrix<5, 5, bool>> marked;
    marked.resize(input.boards.size(), {});

    for (const auto value : input.values) {
        // Mark boards
        size_t i = 0;
        for (const auto& board : input.boards) {
            for (auto y = 0; y < 5; ++y) {
                for (auto x = 0; x < 5; ++x) {
                    if (board(y, x) == value) {
                        // Mark and check for bingo
                        marked[i](y, x) = true;
                        if (hasBingo(marked[i], x, y)) {
                            return sumUnmarked(board, marked[i]) * value;
                        }
                    }
                }
            }
            ++i;
        }
    }
    return 0;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    std::vector<Matrix<5, 5, bool>> marked;
    marked.resize(input.boards.size(), {});
    std::set<int> finished{};

    int lastWin{0};
    for (const auto value : input.values) {
        // Mark boards
        int i = 0;
        for (const auto& board : input.boards) {
            if (finished.contains(i)) {
                ++i;
                continue;
            }
            for (auto y = 0; y < 5; ++y) {
                for (auto x = 0; x < 5; ++x) {
                    if (board(y, x) == value) {
                        // Mark and check for bingo
                        marked[i](y, x) = true;
                        if (hasBingo(marked[i], x, y)) {
                            lastWin = sumUnmarked(board, marked[i]) * value;
                            finished.emplace(i);
                        }
                    }
                }
            }
            ++i;
        }
    }
    return lastWin;
}
