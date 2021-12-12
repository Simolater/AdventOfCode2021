#include <iostream>
#include <array>
#include <vector>
#include "Matrix.h"

namespace AoC {

    void day1(std::ifstream& file) {
        std::vector<int> values;
        std::string line;
        while(std::getline(file, line)) {
            values.push_back(std::stoi(line));
        }

        // Evaluate
        int basic_count = 0;
        int sliding_count = 0;

        for (int i = 1; i < values.size(); ++i) {
            if (values[i] > values[i - 1]) ++basic_count;
        }

        for (int i = 3; i < values.size(); ++i) {
            if (values[i-3] < values[i]) ++sliding_count;
        }

        std::cout << "Increases: " << basic_count << " Sliding: " << sliding_count << std::endl << std::endl;
    }
}