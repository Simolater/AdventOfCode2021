#include <iostream>
#include <stack>
#include <map>
#include "Matrix.h"

namespace AoC {

    void day10(std::ifstream& file) {
        const std::unordered_map<char8_t, char8_t> bracketsMap{
                {'(', ')'},
                {'{', '}'},
                {'[', ']'},
                {'<', '>'},
        };

        const std::unordered_map<char8_t, uint64_t> errorScoreMap{
                {')', 3},
                {']', 57},
                {'}', 1197},
                {'>', 25137},
        };

        const std::unordered_map<char8_t, uint64_t> completeScoreMap{
                {'(', 1},
                {'[', 2},
                {'{', 3},
                {'<', 4},
        };

        uint64_t errorScore{0};
        std::vector<uint64_t> autoCompleteScores;
        std::string line;
        while(std::getline(file, line)) {
            std::stack<char8_t> brackets;
            bool isInvalid = false;
            for (const auto c : line) {
                if (bracketsMap.contains(c)) {
                    brackets.push(c);
                } else {
                    const auto opener = brackets.top();
                    if (bracketsMap.at(opener) != c) {
                        // Invalid char
                        errorScore += errorScoreMap.at(c);
                        isInvalid = true;
                        break;
                    }
                    brackets.pop();
                }
            }
            if (isInvalid) continue;
            uint64_t score{0};
            while(!brackets.empty()) {
                score *= 5;
                score += completeScoreMap.at(brackets.top());
                brackets.pop();
            }
            autoCompleteScores.push_back(score);
        }

        std::sort(autoCompleteScores.begin(), autoCompleteScores.end());

        std::cout << "Error score: " << errorScore << std::endl;
        std::cout << "Middle autocomplete score: " << autoCompleteScores[autoCompleteScores.size() / 2] << std::endl;
    }
}