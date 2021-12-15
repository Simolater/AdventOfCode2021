//
// Created by Simon on 12/12/2021.
//
#pragma once
#include "AoCDay.h"
#include "Days.h"
#include <sstream>
#include <iostream>

namespace AoC {

    constexpr std::size_t NUM_DAYS = 15;

    enum RunConfig {
        runA = 0b01,
        runB = 0b10,
        runTest = 0b100,
        runAll = runA | runB | runTest,
    };

    template <std::size_t day>
    void run_intern(RunConfig config, const std::filesystem::path& inputDirectory) {
        std::cout << "------------Day "<< day <<"------------" << std::endl;

        if (config & RunConfig::runTest) {
            if (!test<day>(config, inputDirectory)) return;
        }
        std::filesystem::path fileName{"day" + std::to_string(day) + "_input.txt"};
        auto fullPath = inputDirectory / fileName;
        std::ifstream file{fullPath};
        if (!file) {
            std::cout << "Failed to open input file: " << fullPath << std::endl;
            return;
        }

        auto input = AoCDay<day>::parseInput(file);

        if (config & RunConfig::runA) {
            const auto result = AoCDay<day>::runA(input);
            std::cout << "Part one: " << result << std::endl;
        }
        if (config & RunConfig::runB) {
            const auto result = AoCDay<day>::runB(input);
            std::cout << "Part two: " << result << std::endl;
        }
    }

    template <std::size_t day>
    bool test(RunConfig config, const std::filesystem::path& inputDirectory) {
        std::filesystem::path testDir{"tests"};
        std::filesystem::path fileName{"day" + std::to_string(day) + "_test.txt"};
        auto fullPath = inputDirectory / testDir / fileName;
        std::ifstream file{fullPath};
        if (!file) {
            std::cout << "Failed to open test input file: " << fullPath << std::endl;
            return false;
        }

        std::string header;
        if (!std::getline(file, header)) {
            std::cout << "Unable to find test header!" << std::endl;
            return false;
        }
        std::stringstream headerStream{header};
        std::string expectedAStr, expectedBStr;
        if (!(std::getline(headerStream, expectedAStr, ' ') && std::getline(headerStream, expectedBStr))) {
            std::cout << "Invalid test header!" << std::endl;
            return false;
        }
        long expectedA{std::stol(expectedAStr)}, expectedB{std::stol(expectedBStr.erase(expectedBStr.size() - 1))};

        auto input = AoCDay<day>::parseInput(file);

        if (config & RunConfig::runA) {
            auto result = AoCDay<day>::runA(input);
            if (result != expectedA) {
                std::cout << "Failed test in part one! Expected " << expectedA << " but was " << result << std::endl;
                return false;
            }
        }
        if (config & RunConfig::runB) {
            auto result = AoCDay<day>::runB(input);
            if (result != expectedB) {
                std::cout << "Failed test in part two! Expected " << expectedB << " but was " << result << std::endl;
                return false;
            }
        }

        return true;
    }

    template <typename T, typename F, T... I>
    bool to_const(T value, F&& fn, std::integer_sequence<T, I...>) {
        return ((value == I && (fn(std::integral_constant<T, I>{}), true)) || ...);
    }

    template <std::size_t Size, typename T, typename F>
    bool to_const(T value, F&& fn) {
        return to_const(value, fn, std::make_integer_sequence<T, Size>{});
    }

    void run(std::size_t day, RunConfig config, const std::filesystem::path& inputDirectory) {
        bool found = to_const<AoC::NUM_DAYS>(day, [&inputDirectory, config](auto I) {
            AoC::run_intern<I + 1>(config, inputDirectory);
        });

        if (!found) {
            std::cout << "Invalid day!" << std::endl;
        }
    }
}
