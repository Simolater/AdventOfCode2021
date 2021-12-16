//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <queue>

constexpr size_t c_day = 16;

template<size_t bitCount>
uint64_t btoi(std::array<char, bitCount> bits) {
    uint64_t result{0};
    for (const auto& bit : bits) {
        result <<= 1;
        if (bit == '1') ++result;
    }
    return result;
}

template<size_t bitCount>
inline uint64_t readInt(std::stringstream& bitStream) {
    std::array<char, bitCount> header{};
    bitStream.read(header.data(), bitCount);
    return btoi(header);
}

AoC::AoCDay<c_day>::packet readPacket(std::stringstream& bitStream) {
    AoC::AoCDay<c_day>::packet packet;
    // Read header
    packet.version = static_cast<decltype(packet.version)>(readInt<3>(bitStream));
    packet.typeId = static_cast<decltype(packet.version)>(readInt<3>(bitStream));

    if (packet.typeId == 4) {
        // literal
        char prefix;
        do {
            bitStream.get(prefix);
            packet.value = (packet.value << 4) + readInt<4>(bitStream);
            packet.size += 5;
        } while (prefix == '1');
    } else {
        // operator
        char lengthTypeId;
        bitStream.get(lengthTypeId);
        ++packet.size;
        if (lengthTypeId == '0') {
            // sub packets in bits
            auto length = readInt<15>(bitStream);
            packet.size += 15;
            while (length > 0) {
                auto sub = readPacket(bitStream);
                packet.size += sub.size;
                length -= sub.size;
                packet.subPackets.emplace_back(std::move(sub));
            }
        } else {
            // sub packets in count
            auto count = readInt<11>(bitStream);
            packet.size += 11;
            for (auto i = 0; i < count; ++i) {
                auto sub = readPacket(bitStream);
                packet.size += sub.size;
                packet.subPackets.emplace_back(std::move(sub));
            }
        }
    }
    return packet;
}

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    std::string message;
    std::getline(input, message);
    if (message.ends_with('\r')) {
        message = message.erase(message.size() - 1);
    }
    std::stringstream bitStream;
    for (const auto& var : message) {
        switch (var) {
            case '0':
                bitStream << "0000";
                break;
            case '1':
                bitStream << "0001";
                break;
            case '2':
                bitStream << "0010";
                break;
            case '3':
                bitStream << "0011";
                break;
            case '4':
                bitStream << "0100";
                break;
            case '5':
                bitStream << "0101";
                break;
            case '6':
                bitStream << "0110";
                break;
            case '7':
                bitStream << "0111";
                break;
            case '8':
                bitStream << "1000";
                break;
            case '9':
                bitStream << "1001";
                break;
            case 'A':
                bitStream << "1010";
                break;
            case 'B':
                bitStream << "1011";
                break;
            case 'C':
                bitStream << "1100";
                break;
            case 'D':
                bitStream << "1101";
                break;
            case 'E':
                bitStream << "1110";
                break;
            case 'F':
                bitStream << "1111";
                break;
            default:
                break;
        }
    }
    auto output = readPacket(bitStream);
    return output;
}

AoC::day_result_t sumVersion(const AoC::AoCDay<c_day>::packet& packet) {
    AoC::day_result_t sum{packet.version};
    for (const auto& sub : packet.subPackets) {
        sum += sumVersion(sub);
    }
    return sum;
}

AoC::day_result_t evaluate(const AoC::AoCDay<c_day>::packet& packet) {
    AoC::day_result_t result{0};
    switch (packet.typeId) {
        case 4: // literal type
            result = static_cast<AoC::day_result_t>(packet.value);
        case 0: // Sum
            for (const auto& sub : packet.subPackets) result += evaluate(sub);
            break;
        case 1: // Product
            result = 1;
            for (const auto& sub : packet.subPackets) result *= evaluate(sub);
            break;
        case 2: // Minimum
            result = std::numeric_limits<decltype(result)>::max();
            for (const auto& sub : packet.subPackets) result = std::min(result, evaluate(sub));
            break;
        case 3: // Maximum
            result = std::numeric_limits<decltype(result)>::min();
            for (const auto& sub : packet.subPackets) result = std::max(result, evaluate(sub));
            break;
        case 5: // greater than
            result = evaluate(packet.subPackets[0]) > evaluate(packet.subPackets[1]) ? 1 : 0;
            break;
        case 6: // less than
            result = evaluate(packet.subPackets[0]) < evaluate(packet.subPackets[1]) ? 1 : 0;
            break;
        case 7: // equal
            result = evaluate(packet.subPackets[0]) == evaluate(packet.subPackets[1]) ? 1 : 0;
            break;
        default:
            break;
    }
    return result;
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    return sumVersion(input);
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    return evaluate(input);
}