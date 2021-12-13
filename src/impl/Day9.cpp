//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <set>

constexpr size_t c_day = 9;

using Pos = std::pair<int, int>;

template<int width, int height>
void calculateBasin(const AoC::Matrix<100, 100, uint8_t>& map, std::set<Pos>& basin, Pos pos) {
    if (basin.contains(pos)) return;
    auto x = pos.first, y = pos.second;
    auto value = map(x, y);
    if (value == 9) return;
    basin.insert(pos);

    if (x > 0 &&          map(x - 1, y) > value) calculateBasin<width, height>(map, basin, {x - 1, y});
    if (x < width - 1 &&  map(x + 1, y) > value) calculateBasin<width, height>(map, basin, {x + 1, y});
    if (y > 0 &&          map(x, y - 1) > value) calculateBasin<width, height>(map, basin, {x, y - 1});
    if (y < height - 1 && map(x, y + 1) > value) calculateBasin<width, height>(map, basin, {x, y + 1});
}

template<int width, int height>
std::vector<Pos> calculateLowPoints(const AoC::Matrix<100, 100, uint8_t>& map) {
    std::vector<Pos> lowPoints;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto value = map(i, j);
            if (i > 0 && map(i - 1, j) <= value) continue;
            if (i < width - 1 && map(i + 1, j) <= value) continue;
            if (j > 0 && map(i, j - 1) <= value) continue;
            if (j < height - 1 && map(i, j + 1) <= value) continue;
            lowPoints.emplace_back(i, j);
        }
    }
    return lowPoints;
}

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    int x = 0;
    int y = 0;
    for (std::string line; std::getline(input, line);) {
        for (auto num : line) {
            if (num == '\r') continue;
            output.map(x, y) = num - '0';
            ++x;
        }
        output.width = x;
        x = 0;
        ++y;
    }
    output.height = y;
    return output;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    std::vector<Pos> lowPoints;
    if (input.width == 10 && input.height == 5) {
        lowPoints = calculateLowPoints<10, 5>(input.map);
    } else if (input.width == 100 && input.height == 100) {
        lowPoints = calculateLowPoints<100, 100>(input.map);
    }
    day_result_t result{0};
    for (const auto& point : lowPoints) {
        result += input.map(point.first, point.second) + 1;
    }
    return result;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    std::vector<day_result_t> basinSizes;
    if (input.width == 10 && input.height == 5) {
        for (const auto& point : calculateLowPoints<10, 5>(input.map)) {
            std::set<Pos> basin;
            calculateBasin<10, 5>(input.map, basin, point);
            basinSizes.push_back(static_cast<day_result_t>(basin.size()));
        }
    } else if (input.width == 100 && input.height == 100) {
        for (const auto& point : calculateLowPoints<100, 100>(input.map)) {
            std::set<Pos> basin;
            calculateBasin<100, 100>(input.map, basin, point);
            basinSizes.push_back(static_cast<day_result_t>(basin.size()));
        }
    }
    std::sort(basinSizes.begin(), basinSizes.end(), std::greater());
    return basinSizes[0] * basinSizes[1] * basinSizes[2];
}
