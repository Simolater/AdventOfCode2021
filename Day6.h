#include <initializer_list>
#include <array>
#include "Matrix.h"

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



    void day6(std::ifstream& file) {
        Matrix<1, 9> input{0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::string val;
        while (std::getline(file, val, ',')) {
            ++input(0, std::stoi(val));
        }

        constexpr auto mat_80 = Population<80>::value;
        constexpr auto mat_256 = Population<256>::value;

        std::cout << "Amount of fish: " << std::endl;
        std::cout << "After  80 days: " << (input * mat_80).sum() << std::endl;
        std::cout << "After 256 days: " << (input * mat_256).sum() << std::endl;
    };
}