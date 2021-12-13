//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"

constexpr size_t c_day = 11;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;

    std::string line;
    for(auto y = 0; std::getline(input, line); ++y) {
        int x = 0;
        for (const auto val : line) {
            if (x >= 10) break;
            output(x, y) = val - '0';
            ++x;
        }
    }
    return output;
}

AoC::day_result_t simulateStep(AoC::AoCDay<c_day>::input_t& grid) {
    for (auto y = 0; y < 10; ++y) {
        for (auto x = 0; x < 10; ++x) {
            ++grid(x, y);
        }
    }
    std::vector<std::pair<int, int>> flashed;
    for (auto y = 0; y < 10; ++y) {
        for (auto x = 0; x < 10; ++x) {
            if (grid(x, y) == 10) flashed.emplace_back(x, y);
        }
    }
    for (auto index = 0; index < flashed.size(); ++index) {
        auto startX = flashed[index].first, startY = flashed[index].second;
        for (int y = startY - 1; y <= startY + 1; ++y) {
            for (int x = startX - 1; x <= startX + 1; ++x) {
                if (x < 0 || x >= 10) continue;
                if (y < 0 || y >= 10) continue;
                if (++grid(x, y) == 10) {
                    flashed.emplace_back(x, y);
                }
            }
        }
    }
    for (auto y = 0; y < 10; ++y) {
        for (auto x = 0; x < 10; ++x) {
            if (grid(x, y) > 9) {
                grid(x, y) = 0;
            }
        }
    }
    return static_cast<AoC::day_result_t>(flashed.size());
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    input_t grid{input};
    day_result_t count{0};
    for (auto i = 0; i < 100; ++i) {
        count += simulateStep(grid);
    }
    return count;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    input_t grid{input};
    day_result_t steps{1};
    for (; simulateStep(grid) != 100; ++steps);
    return steps;
}
