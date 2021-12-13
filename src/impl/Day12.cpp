//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <map>
#include <set>

constexpr size_t c_day = 12;

AoC::day_result_t traverse(const std::unordered_map<std::string, std::vector<std::string>>& adjacency, std::set<std::string>& visited, const std::string& current, bool doubleVisit) {
    bool isDoubleVisit{false};
    if (current == "end") return 1;
    // visited only contains small caves
    if (visited.contains(current)) {
        if (doubleVisit && current != "start") {
            isDoubleVisit = true;
        } else {
            return 0;
        }
    }
    if (islower(current[0])) visited.emplace(current);
    AoC::day_result_t paths{0};
    for (const auto& next : adjacency.at(current)) {
        paths += traverse(adjacency, visited, next, doubleVisit && !isDoubleVisit);
    }
    if (!isDoubleVisit) visited.erase(current);
    return paths;
}

AoC::day_result_t traverse(const std::unordered_map<std::string, std::vector<std::string>>& adjacency, bool doubleVisit = false) {
    std::set<std::string> visited;
    return traverse(adjacency, visited, "start", doubleVisit);
}

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string line; std::getline(input, line);) {
        if (line.ends_with('\r')) {
            line = line.erase(line.size() - 1);
        }
        std::stringstream inputStream{line};
        std::string left, right;
        std::getline(inputStream, left, '-');
        std::getline(inputStream, right, '-');

        if (output.contains(left)) {
            output[left].push_back(right);
        } else {
            output[left] = {right};
        }

        if (output.contains(right)) {
            output[right].push_back(left);
        } else {
            output[right] = {left};
        }
    }
    return output;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    return traverse(input);
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    return traverse(input, true);
}
