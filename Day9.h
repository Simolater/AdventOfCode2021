#include <iostream>
#include <set>
#include "Matrix.h"

namespace AoC {

    using Pos = std::pair<int, int>;

    template<int width, int height>
    void calculateBasin(const Matrix<width, height, uint8_t>& map, std::set<Pos>& basin, Pos pos) {
        if (basin.contains(pos)) return;
        auto x = pos.first, y = pos.second;
        auto value = map(x, y);
        if (value == 9) return;
        basin.insert(pos);

        if (x > 0 &&          map(x - 1, y) > value) calculateBasin(map, basin, {x - 1, y});
        if (x < width - 1 &&  map(x + 1, y) > value) calculateBasin(map, basin, {x + 1, y});
        if (y > 0 &&          map(x, y - 1) > value) calculateBasin(map, basin, {x, y - 1});
        if (y < height - 1 && map(x, y + 1) > value) calculateBasin(map, basin, {x, y + 1});
    }

    void day9(std::ifstream& file) {
        constexpr auto width = 100, height = 100;

        Matrix<width, height, uint8_t> map;

        std::string line;
        int x = 0, y = 0;
        while (std::getline(file, line)) {
            for (auto num : line) {
                map(x, y) = num - '0';
                ++x;
            }
            x = 0;
            ++y;
        }

        uint64_t marked_sum = 0;
        std::vector<uint64_t> basinSizes;

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                auto value = map(i, j);
                if (i > 0 && map(i - 1, j) <= value) continue;
                if (i < width - 1 && map(i + 1, j) <= value) continue;
                if (j > 0 && map(i, j - 1) <= value) continue;
                if (j < height - 1 && map(i, j + 1) <= value) continue;
                marked_sum += value + 1;

                std::set<Pos> basin;
                calculateBasin<width, height>(map, basin, {i, j});
                basinSizes.push_back(basin.size());
            }
        }

        std::sort(basinSizes.begin(), basinSizes.end(), std::greater());

        std::cout << "Total risk level: " << marked_sum << std::endl;
        std::cout << "Basins: " << basinSizes[0] * basinSizes[1] * basinSizes[2] << std::endl;
    }
}