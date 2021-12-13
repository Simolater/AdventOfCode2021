//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <unordered_map>
#include <stack>

constexpr size_t c_day = 10;

const std::unordered_map<char8_t, char8_t> bracketsMap{
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
        {'<', '>'},
};

const std::unordered_map<char8_t, int64_t> errorScoreMap{
        {')', 3},
        {']', 57},
        {'}', 1197},
        {'>', 25137},
};

const std::unordered_map<char8_t, int64_t> completeScoreMap{
        {'(', 1},
        {'[', 2},
        {'{', 3},
        {'<', 4},
};

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string line; std::getline(input, line);) {
        if (line.ends_with('\r')) {
            line = line.erase(line.size() - 1);
        }
        output.push_back(line);
    }
    return output;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    day_result_t errorScore{0};
    for (const auto& line : input) {
        std::stack<char8_t> brackets;
        for (const auto c : line) {
            if (bracketsMap.contains(c)) {
                brackets.push(c);
            } else {
                const auto opener = brackets.top();
                if (bracketsMap.at(opener) != c) {
                    // Invalid char
                    errorScore += errorScoreMap.at(c);
                    break;
                }
                brackets.pop();
            }
        }
    }
    return errorScore;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    std::vector<int64_t> autoCompleteScores;
    for (const auto& line : input) {
        std::stack<char8_t> brackets;
        bool isInvalid = false;
        for (const auto c : line) {
            if (bracketsMap.contains(c)) {
                brackets.push(c);
            } else {
                const auto opener = brackets.top();
                if (bracketsMap.at(opener) != c) {
                    isInvalid = true;
                    break;
                }
                brackets.pop();
            }
        }
        if (isInvalid) continue;
        int64_t score{0};
        while(!brackets.empty()) {
            score *= 5;
            score += completeScoreMap.at(brackets.top());
            brackets.pop();
        }
        autoCompleteScores.push_back(score);
    }
    std::sort(autoCompleteScores.begin(), autoCompleteScores.end());
    return autoCompleteScores[autoCompleteScores.size() / 2];
}
