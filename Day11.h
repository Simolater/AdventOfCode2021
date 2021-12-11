#include <iostream>
#include <stack>
#include <map>
#include "Matrix.h"

namespace AoC {

    void day11(std::ifstream& file) {
        constexpr int width = 10, height = 10;
        Matrix<width, height> grid;

        std::string input;
        for(auto y = 0; std::getline(file, input); ++y) {
            int x = 0;
            for (const auto val : input) {
                grid(x, y) = val - '0';
                ++x;
            }
        }

        bool allFlashed{false};
        uint64_t allFlashedStep{0};
        uint64_t flashedCount{0};
        for (auto i = 0; i < 100 || !allFlashed; ++i) {
            for (auto y = 0; y < height; ++y) {
                for (auto x = 0; x < width; ++x) {
                    ++grid(x, y);
                }
            }
            std::vector<std::pair<int, int>> flashed;
            for (auto y = 0; y < height; ++y) {
                for (auto x = 0; x < width; ++x) {
                    if (grid(x, y) == 10) flashed.emplace_back(x, y);
                }
            }
            for (auto index = 0; index < flashed.size(); ++index) {
                auto startX = flashed[index].first, startY = flashed[index].second;
                for (int y = startY - 1; y <= startY + 1; ++y) {
                    for (int x = startX - 1; x <= startX + 1; ++x) {
                        if (x < 0 || x >= width) continue;
                        if (y < 0 || y >= height) continue;
                        if (++grid(x, y) == 10) {
                            flashed.emplace_back(x, y);
                        }
                    }
                }
            }
            for (auto y = 0; y < height; ++y) {
                for (auto x = 0; x < width; ++x) {
                    if (grid(x, y) > 9) {
                        grid(x, y) = 0;
                    }
                }
            }
            if (i < 100) flashedCount += flashed.size();
            if (!allFlashed && flashed.size() == 100) {
                allFlashed = true;
                allFlashedStep = i + 1;
            }
        }

        std::cout << "Flash count after 100 steps: " << flashedCount << std::endl;
        std::cout << "First time all flashed: " << allFlashedStep << std::endl;
    }
}