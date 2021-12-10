#include <iostream>
#include <unordered_map>

namespace AoC {

    void day8(std::ifstream& file) {
        std::string line;

        uint64_t uniqueCount = 0, sum = 0;
        while (std::getline(file, line)) {
            std::stringstream lineStream{line};
            std::string measurement, output, value;

            std::unordered_map<std::string, uint8_t> map;
            std::vector<std::string> values;

            std::getline(lineStream, measurement, '|');
            std::getline(lineStream, output);

            std::stringstream measurementStream{measurement};
            while (std::getline(measurementStream, value, ' ')) {
                std::sort(value.begin(), value.end());
                values.push_back(value);
            }

            const auto one = *std::find_if(values.begin(), values.end(), [](const auto& val) {return val.length() == 2;});
            const auto four = *std::find_if(values.begin(), values.end(), [](const auto& val) {return val.length() == 4;});

            const auto intersectSize = [](const std::string& first, const std::string& second) -> size_t {
                std::string intersection;
                std::set_intersection(first.cbegin(), first.cend(), second.cbegin(), second.cend(), std::back_inserter(intersection));
                return intersection.size();
            };

            for (const auto& val : values) {
                switch (val.length()) {
                    case 2:
                        map[val] = 1;
                        break;
                    case 3:
                        map[val] = 7;
                        break;
                    case 4:
                        map[val] = 4;
                        break;
                    case 5:
                        if (intersectSize(one, val) == 2) {
                            map[val] = 3;
                        } else if (intersectSize(four, val) == 2) {
                            map[val] = 2;
                        } else {
                            map[val] = 5;
                        }
                        break;
                    case 6:
                        if (intersectSize(one, val) == 1) {
                            map[val] = 6;
                        } else if (intersectSize(four, val) == 3) {
                            map[val] = 0;
                        } else {
                            map[val] = 9;
                        }
                        break;
                    case 7:
                        map[val] = 8;
                        break;
                }
            }

            uint64_t number{0};
            std::stringstream outputStream{output};
            outputStream.ignore(1); // Ignore space
            while (std::getline(outputStream, value, ' ')) {
                std::sort(value.begin(), value.end());
                const auto len = value.size();
                if (len == 2 || len == 3 || len == 4 || len == 7) ++uniqueCount;
                number = number * 10 + map[value];
            }
            sum += number;
        }
        std::cout << "Easy count: " << uniqueCount << std::endl;
        std::cout << "Sum of Values: " << sum << std::endl;
    }
}