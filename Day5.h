#include <array>
#include <vector>
#include <unordered_map>
#include "Matrix.h"

namespace AoC {

    void day5(std::ifstream& file) {
        using coord_t = uint32_t;

        // Stores the count with and without diagonals
        struct Cell {
            uint32_t countNonDiagonal;
            uint32_t count;

            Cell operator+= (const Cell& other) {
                countNonDiagonal += other.countNonDiagonal;
                count += other.count;
                return *this;
            }
        };

        struct pair_hash
        {
            std::size_t operator() (const std::pair<coord_t, coord_t> &pair) const {
                return std::hash<coord_t>()(pair.first) ^ std::hash<coord_t>()(pair.second);
            }
        };
        std::unordered_map<std::pair<coord_t , coord_t>, Cell, pair_hash> map;

        std::string input;
        while (std::getline(file, input)) {
            int x1, x2, y1, y2;
            std::stringstream inputStream(input);
            std::string value;
            if (!std::getline(inputStream, value, ',')) return;
            x1 = std::stoi(value);
            if (!std::getline(inputStream, value, ' ')) return;
            y1 = std::stoi(value);
            // Skip "-> "
            inputStream.ignore(3);
            if (!std::getline(inputStream, value, ',')) return;
            x2 = std::stoi(value);
            if (!std::getline(inputStream, value, ' ')) return;
            y2 = std::stoi(value);

            // Only increase non-diagonal count when it's a straight line
            Cell offset = {x1 == x2 || y1 == y2, 1};

            // Write initial pos
            { // in scope so I can use pos again later
                auto pos = std::make_pair(x1, y1);
                if (map.contains(pos)) {
                    map[pos] += offset;
                } else {
                    map[pos] = offset;
                }
            }
            // Write steps of the line
            while (x1 != x2 || y1 != y2) {
                auto xDiff = x2 - x1;
                if (xDiff < 0) {
                    --x1;
                } else if (xDiff > 0) {
                    ++x1;
                }
                auto yDiff = y2 - y1;
                if (yDiff < 0) {
                    --y1;
                } else if (yDiff > 0) {
                    ++y1;
                }
                auto pos = std::make_pair(x1, y1);
                if (map.contains(pos)) {
                    map[pos] += offset;
                } else {
                    map[pos] = offset;
                }
            }
        }

        uint64_t countNonDiagonal = 0, count = 0;
        for (auto value : map) {
            if (value.second.countNonDiagonal > 1) ++countNonDiagonal;
            if (value.second.count > 1) ++count;
        }

        std::cout << "Count: " << countNonDiagonal << " With diagonals: " << count << std::endl;
    }
}