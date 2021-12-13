#pragma once

namespace AoC {
    template<int R, int C, typename val_t = long, typename index_t = int>
    requires (R > 0 && C > 0)
    struct Matrix {

        std::array<std::array<val_t, C>, R> m_values = {};

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
}