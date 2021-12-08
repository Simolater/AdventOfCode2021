#include <initializer_list>
#include <array>

namespace AoC {
    template<int R, int C, typename val_t = int64_t, typename index_t = int>
    requires (R > 0 && C > 0)
    struct Matrix {

        std::array<std::array<val_t, C>, R> m_values;

        constexpr val_t& operator() (const index_t index_r, const index_t index_c) {
            return m_values.at(index_r).at(index_c);
        }

        constexpr const val_t& operator() (const index_t index_r, const index_t index_c) const {
            return m_values.at(index_r).at(index_c);
        }

        template<index_t P>
        constexpr auto operator*(const Matrix<C, P>& right) const {
            Matrix<R, P, val_t, index_t> result{};
            for (index_t i = 0; i < R; ++i) {
                for (index_t j = 0; j < P; ++j) {
                    val_t value{0};
                    for (index_t x = 0; x < C; ++x) {
                        value += (*this)(i, x) * right(x, j);
                    }
                    result(i, j) = value;
                }
            }
            return result;
        }

        constexpr val_t sum() const {
            val_t sum{0};
            for (index_t i = 0; i < R; ++i) {
                for (index_t j = 0; j < C; ++j) {
                    sum += (*this)(i, j);
                }
            }
            return sum;
        }
    };

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
    requires((N & 3) == 0)
    struct Population<N> {
        static constexpr auto value{Population<N / 4>::value * Population<N / 4>::value * Population<N / 4>::value * Population<N / 4>::value};
    };

    template<int N>
    requires(!(N & 1) && (N & 3) != 0)
    struct Population<N> {
        static constexpr auto value{Population<N / 2>::value * Population<N / 2>::value};
    };

    template<>
    struct Population<1> {
        static constexpr auto value{PopulationBase::value};
    };



    void day6(std::ifstream& file) {
        std::cout << "------------Day 06------------" << std::endl;
        Matrix<1, 9> input{0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::string val;
        while (std::getline(file, val, ',')) {
            ++input(0, std::stoi(val));
        }

        constexpr auto mat_80 = Population<80>::value;
        constexpr auto mat_256 = Population<100000000000000000>::value;

        std::cout << "Amount of fish: " << std::endl;
        std::cout << "After  80 days: " << (input * mat_80).sum() << std::endl;
        std::cout << "After 256 days: " << (input * mat_256).sum() << std::endl;
    };
}