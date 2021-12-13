//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <sstream>
#include <unordered_map>

constexpr size_t c_day = 8;

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string line; std::getline(input, line);) {
        Measurement measurement;
        std::stringstream lineStream{line};

        std::string measured, out;
        std::getline(lineStream, measured, '|');
        std::getline(lineStream, out);
        std::stringstream measurementStream{measured};
        for (std::string value; std::getline(measurementStream, value, ' ');) {
            std::sort(value.begin(), value.end());
            measurement.measured.push_back(value);
        }
        std::stringstream outStream{out};
        outStream.ignore(1); // Ignore space
        for (std::string value; std::getline(outStream, value, ' ');) {
            if (value.ends_with('\r')) {
                value = value.erase(value.size() - 1);
            }
            std::sort(value.begin(), value.end());
            measurement.output.push_back(value);
        }
        output.push_back(measurement);
    }
    return output;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    day_result_t result{0};
    for (const auto& measurement : input) {
        for (const auto& out : measurement.output) {
            const auto len = out.length();
            if (len == 2 || len == 3 || len == 4 || len == 7) ++result;
        }
    }
    return result;
}

size_t intersectSize(const std::string& first, const std::string& second) {
    std::string intersection;
    std::set_intersection(first.cbegin(), first.cend(), second.cbegin(), second.cend(), std::back_inserter(intersection));
    return intersection.size();
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    day_result_t result{0};
    for (const auto& measurement : input) {
        const auto one = *std::find_if(measurement.measured.begin(), measurement.measured.end(), [](const auto& val) {return val.length() == 2;});
        const auto four = *std::find_if(measurement.measured.begin(), measurement.measured.end(), [](const auto& val) {return val.length() == 4;});

        std::unordered_map<std::string, uint8_t> map;

        for (const auto& value : measurement.measured) {
            switch (value.length()) {
                case 2:
                    map[value] = 1;
                    break;
                case 3:
                    map[value] = 7;
                    break;
                case 4:
                    map[value] = 4;
                    break;
                case 5:
                    if (intersectSize(one, value) == 2) {
                        map[value] = 3;
                    } else if (intersectSize(four, value) == 2) {
                        map[value] = 2;
                    } else {
                        map[value] = 5;
                    }
                    break;
                case 6:
                    if (intersectSize(one, value) == 1) {
                        map[value] = 6;
                    } else if (intersectSize(four, value) == 3) {
                        map[value] = 0;
                    } else {
                        map[value] = 9;
                    }
                    break;
                case 7:
                    map[value] = 8;
                    break;
            }
        }

        day_result_t number{0};
        for (const auto& value : measurement.output) {
            number = number * 10 + map[value];
        }
        result += number;
    }
    return result;
}
