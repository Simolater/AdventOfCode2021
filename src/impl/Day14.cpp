//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <map>
#include <set>

constexpr size_t c_day = 14;

template <typename T, typename R, typename Hash>
void addIfContains(std::unordered_map<T, R, Hash>& map, const T& key, const R& val) {
    if (map.contains(key)) {
        map[key] += val;
    } else {
        map[key] = val;
    }
}

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    std::string startingValue;
    std::getline(input, startingValue);
    if (startingValue.ends_with('\r')) {
        startingValue = startingValue.erase(startingValue.size() - 1);
    }
    output.start = startingValue.at(0);
    output.end = startingValue.at(startingValue.length() - 1);
    for (auto i = 1; i < startingValue.length(); ++i) {
        charPair pair{startingValue[i - 1], startingValue[i]};
        addIfContains(output.pairs, pair, 1l);
    }
    std::getline(input, startingValue);

    for (std::string line; std::getline(input, line);) {
        if (line.ends_with('\r')) {
            line = line.erase(line.size() - 1);
        }
        output.rules[{line.at(0), line.at(1)}] = line.at(line.length() - 1);
    }
    return output;
}

void runStep(decltype(AoC::AoCDay<c_day>::input_t::pairs)& pairs, const decltype(AoC::AoCDay<c_day>::input_t::rules)& rules) {
    decltype(AoC::AoCDay<c_day>::input_t::pairs) newPairs{};
    for (const auto& pair : pairs) {
        if (rules.contains(pair.first)) {
            const auto& newChar = rules.at(pair.first);
            addIfContains(newPairs, {pair.first.first, newChar}, pair.second);
            addIfContains(newPairs, {newChar, pair.first.second}, pair.second);
        } else {
            addIfContains(newPairs, pair.first, pair.second);
        }
    }
    pairs = std::move(newPairs);
};

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    auto pairs{input.pairs};
    for (auto i = 0; i < 10; ++i) {
        runStep(pairs, input.rules);
    }
    std::unordered_map<char8_t, int64_t> count;
    for (const auto& value : pairs) {
        addIfContains(count, value.first.first, value.second);
        addIfContains(count, value.first.second, value.second);
    }
    addIfContains(count, input.start, 1l);
    addIfContains(count, input.end, 1l);
    int64_t leastCommon = count.begin()->second, mostCommon = count.begin()->second;
    for (const auto& entry : count) {
        if (entry.second < leastCommon) {
            leastCommon = entry.second;
        } else if (entry.second > mostCommon) {
            mostCommon = entry.second;
        }
    }
    return (mostCommon - leastCommon) / 2;
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    auto pairs{input.pairs};
    for (auto i = 0; i < 40; ++i) {
        runStep(pairs, input.rules);
    }
    std::unordered_map<char8_t, int64_t> count;
    for (const auto& value : pairs) {
        addIfContains(count, value.first.first, value.second);
        addIfContains(count, value.first.second, value.second);
    }
    addIfContains(count, input.start, 1l);
    addIfContains(count, input.end, 1l);
    int64_t leastCommon = count.begin()->second, mostCommon = count.begin()->second;
    for (const auto& entry : count) {
        if (entry.second < leastCommon) {
            leastCommon = entry.second;
        } else if (entry.second > mostCommon) {
            mostCommon = entry.second;
        }
    }
    return (mostCommon - leastCommon) / 2;
}
