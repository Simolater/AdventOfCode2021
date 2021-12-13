//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"

constexpr size_t c_day = 6;

namespace AoC {
    struct PopulationBase {
        static constexpr Matrix<9, 9> value{
                0,0,0,0,0,0,1,0,1,
                1,0,0,0,0,0,0,0,0,
                0,1,0,0,0,0,0,0,0,
                0,0,1,0,0,0,0,0,0,
                0,0,0,1,0,0,0,0,0,
                0,0,0,0,1,0,0,0,0,
                0,0,0,0,0,1,0,0,0,
                0,0,0,0,0,0,1,0,0,
                0,0,0,0,0,0,0,1,0,
        };
    };

    template <int N>
    struct Population {
        static constexpr auto value{Population<N - 1>::value * PopulationBase::value};
    };

    template<int N>
    requires(!(N & 1))
    struct Population<N> {
        static constexpr auto value{Population<N / 2>::value * Population<N / 2>::value};
    };

    template<>
    struct Population<1> {
        static constexpr auto value{PopulationBase::value};
    };
}

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output{0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (std::string val; std::getline(input, val, ',');) {
        ++output(0, std::stoi(val));
    }
    return output;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    constexpr auto mat = Population<80>::value;
    return (input * mat).sum();
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    constexpr auto mat = Population<256>::value;
    return (input * mat).sum();
}
