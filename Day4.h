#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include "Matrix.h"

namespace AoC {

    void day4(std::ifstream& file) {
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