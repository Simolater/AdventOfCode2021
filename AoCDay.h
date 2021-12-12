#include <sstream>
#pragma once

template <typename Parse_t>
class AoCDay {

    virtual Parse_t parseInput(std::stringstream& input) = 0;


private:

    Parse_t parsedData;
};
