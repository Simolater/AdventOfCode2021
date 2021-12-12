#include <initializer_list>
#include <array>
#include <iostream>
#include <vector>
#include "Matrix.h"

namespace AoC {

    void day7(std::ifstream& file) {

        std::vector<int64_t> crabs;

        std::string input;
        while (std::getline(file, input, ',')) {
            crabs.push_back(std::stoi(input));
        }

        int64_t lowestCost = std::numeric_limits<int64_t>::max(), at = 0;
        int64_t lowestCostB = std::numeric_limits<int64_t>::max(), atB = 0;
        for (auto i = 0; i < 1000; ++i) {
            // Calculate cost
            int64_t cost = 0, costB = 0;
            for (const auto& pos : crabs) {
                auto mov = std::abs(pos - i);
                cost += mov;
                costB += (mov * (mov + 1)) / 2;
            }
            if (cost < lowestCost) {
                lowestCost = cost;
                at = i;
            }
            if (costB < lowestCostB) {
                lowestCostB = costB;
                atB = i;
            }
        }

        std::cout << "At: " << at << " Cost: " << lowestCost << std::endl;
        std::cout << "At: " << atB << " Cost: " << lowestCostB << std::endl;
    }
}