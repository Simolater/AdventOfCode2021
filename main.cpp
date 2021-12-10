#include <iostream>
#include <fstream>
#include <string>
#include "week_one.h"
#include "Day6.h"
#include "Day8.h"
#include "Day9.h"
#include "Day10.h"

int main(int argv, char** args) {
    if (argv != 3) {
        std::cout << "Provide an input file and the day!" << std::endl;
        return 1;
    }
    std::ifstream file(args[1]);
    if (!file) {
        std::cout << "Failed to open file!" << std::endl;
        return 2;
    }
    // This could be unsafe but idc

    const auto day = std::stoi(args[2]);
    std::cout << "------------Day "<< day <<"------------" << std::endl;
    switch (day) {
        case 1:
            AoC::day1(file);
            break;
        case 2:
            AoC::day2(file);
            break;
        case 3:
            AoC::day3(file);
            break;
        case 4:
            AoC::day4(file);
            break;
        case 5:
            AoC::day5(file);
            break;
        case 6:
            AoC::day6(file);
            break;
        case 7:
            AoC::day7(file);
            break;
        case 8:
            AoC::day8(file);
            break;
        case 9:
            AoC::day9(file);
            break;
        case 10:
            AoC::day10(file);
            break;
        default:
            std::cout << "Invalid day" << std::endl;
            break;
    }
    file.close();
    return 0;
}
