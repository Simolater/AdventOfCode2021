//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <unordered_map>

constexpr size_t c_day = 5;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string in; std::getline(input, in);) {
        Line line;
        std::stringstream inputStream(in);
        std::string value;
        if (!std::getline(inputStream, value, ',')) return output;
        line.x1 = std::stoi(value);
        if (!std::getline(inputStream, value, ' ')) return output;
        line.y1 = std::stoi(value);
        // Skip "-> "
        inputStream.ignore(3);
        if (!std::getline(inputStream, value, ',')) return output;
        line.x2 = std::stoi(value);
        if (!std::getline(inputStream, value, ' ')) return output;
        line.y2 = std::stoi(value);
        output.push_back(line);
    }
    return output;
}

struct pair_hash
{
    std::size_t operator() (const std::pair<int, int> &pair) const {
        return std::hash<int>()(pair.first) ^ std::hash<int>()(pair.second);
    }
};

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    std::unordered_map<std::pair<int , int>, int, pair_hash> map;
    day_result_t count{0};
    for (const auto& line : input) {
        int x1 = line.x1, y1 = line.y1, x2 = line.x2, y2 = line.y2;
        if (!(x1 == x2 || y1 == y2)) continue;
        { // in scope so I can use pos again later
            auto pos = std::make_pair(x1, y1);
            if (map.contains(pos)) {
                ++map[pos];
                if (map[pos] == 2) ++count;
            } else {
                map[pos] = 1;
            }
        }
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
                ++map[pos];
                if (map[pos] == 2) ++count;
            } else {
                map[pos] = 1;
            }
        }
    }
    return count;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    std::unordered_map<std::pair<int , int>, int, pair_hash> map;
    day_result_t count{0};
    for (const auto& line : input) {
        int x1 = line.x1, y1 = line.y1, x2 = line.x2, y2 = line.y2;
        { // in scope so I can use pos again later
            auto pos = std::make_pair(x1, y1);
            if (map.contains(pos)) {
                ++map[pos];
                if (map[pos] == 2) ++count;
            } else {
                map[pos] = 1;
            }
        }
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
                ++map[pos];
                if (map[pos] == 2) ++count;
            } else {
                map[pos] = 1;
            }
        }
    }
    return count;
}
