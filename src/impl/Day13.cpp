//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <map>
#include <set>

constexpr size_t c_day = 13;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string line; std::getline(input, line);) {
        if (line.ends_with('\r')) {
            line = line.erase(line.size() - 1);
        }
        if (line.empty()) break;
        std::stringstream lineStream{line};
        std::string value;
        std::getline(lineStream, value, ',');
        const int64_t x = std::stol(value);
        std::getline(lineStream, value);
        const int64_t y = std::stol(value);
        output.points.emplace(x, y);
    }
    for (std::string line; std::getline(input, line);) {
        std::stringstream lineStream{line};
        lineStream.ignore(11);
        std::string value;
        std::getline(lineStream, value, '=');
        const char8_t axis = value[0];
        std::getline(lineStream, value);
        const int64_t pos = std::stol(value);
        output.folds.emplace_back(axis, pos);
    }
    return output;
}

AoC::AoCDay<c_day>::input_points_t fold(const AoC::AoCDay<c_day>::input_points_t& points, char8_t axis, uint64_t value) {
    AoC::AoCDay<c_day>::input_points_t newPoints;
    if (axis == 'x') {
        for (const auto& point : points) {
            if (point.first == value) continue;
            const auto newPos = point.first >= value ? point.first - (point.first - value) * 2 : point.first;
            newPoints.emplace(newPos, point.second);
        }
    } else {
        for (const auto& point : points) {
            if (point.second == value) continue;
            const auto newPos = point.second >= value ? point.second - (point.second - value) * 2 : point.second;
            newPoints.emplace(point.first, newPos);
        }
    }
    return newPoints;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    const auto& firstFold = input.folds[0];
    return static_cast<day_result_t>(fold(input.points, firstFold.first, firstFold.second).size());
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    auto points{input.points};
    for (const auto& foldInst : input.folds) {
        points = std::move(fold(points, foldInst.first, foldInst.second));
    }
    // For printing the answer, I'm not writing code to parse this
    /*for (auto y = 0; y < 20; ++y) {
        for (auto x = 0; x < 20; ++x) {
            std::cout << (points.contains({x, y}) ? '#' : '.');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
    return static_cast<day_result_t>(points.size());
}
