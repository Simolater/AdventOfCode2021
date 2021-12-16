//
// Created by Simon on 12/12/2021.
//
#pragma once
#include "AoCDay.h"
#include "../Matrix.h"
#include <vector>
#include <set>
#include <unordered_map>

namespace AoC {

    using day_result_t = int64_t;

    template <>
    struct AoCDay<1> {

        using input_t = std::vector<int>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<2> {

        using input_t = std::vector<std::pair<int, int>>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<3> {

        using input_t = std::vector<std::string>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<4> {

        struct input_t {
            std::vector<int> values;
            std::vector<Matrix<5, 5, int>> boards;
        };

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<5> {

        struct Line {
            int x1, y1, x2, y2;
        };

        using input_t = std::vector<Line>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<6> {

        using input_t = Matrix<1, 9>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<7> {

        using input_t = std::vector<int64_t>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<8> {

        struct Measurement {
            std::vector<std::string> measured;
            std::vector<std::string> output;
        };

        using input_t = std::vector<Measurement>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<9> {

        struct input_t {
            int64_t width{0}, height{0};
            Matrix<100, 100, uint8_t> map;
        };

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<10> {

        using input_t = std::vector<std::string>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<11> {

        using input_t = Matrix<10, 10>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<12> {

        using input_t = std::unordered_map<std::string, std::vector<std::string>>;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<13> {

        using input_points_t = std::set<std::pair<int64_t, int64_t>>;

        struct input_t {
            input_points_t points;
            std::vector<std::pair<char8_t, int64_t>> folds;
        };

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<14> {

        struct pair_hash
        {
            std::size_t operator() (const std::pair<int, int> &pair) const {
                return std::hash<int>()(pair.first) ^ std::hash<int>()(pair.second);
            }
        };

        using charPair = std::pair<char8_t, char8_t>;

        struct input_t {
            char8_t start, end;
            std::unordered_map<charPair, int64_t, pair_hash> pairs;
            std::unordered_map<charPair, char8_t, pair_hash> rules;
        };

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<15> {

        struct input_t {
            int64_t width{0}, height{0};
            std::vector<int64_t> grid;
        };

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };

    template <>
    struct AoCDay<16> {

        struct packet {
            uint8_t version{0}, typeId{0};
            uint64_t value{0}, size{6};
            std::vector<packet> subPackets;
        };

        using input_t = packet;

        static input_t parseInput(std::istream& input);

        static day_result_t runA(const input_t& input);

        static day_result_t runB(const input_t& input);

    };
}
