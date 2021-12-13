#include <iostream>
#include <string>
#include "src/AoC.h"

int main(int argv, char** args) {
    if (argv != 3) {
        std::cout << "Provide an input file and the day!" << std::endl;
        return 1;
    }
    std::filesystem::path inputDirectory(args[1]);
    // This could be unsafe but idc
    const std::size_t day = std::stoi(args[2]) - 1;

    AoC::run(day, AoC::RunConfig::runAll, inputDirectory);

    return 0;
}
