//
// Created by Simon on 12/12/2021.
//
#include "../Days.h"
#include <queue>

constexpr size_t c_day = 15;
constexpr int64_t INF = std::numeric_limits<int64_t>::max();

AoC::AoCDay<c_day>::input_t AoC::AoCDay<c_day>::parseInput(std::istream &input) {
    input_t output;
    for (std::string line; std::getline(input, line);) {
        if (line.ends_with('\r')) {
            line = line.erase(line.size() - 1);
        }
        output.width = static_cast<int64_t>(line.length());
        for (const auto& c : line) {
            output.grid.push_back(c - '0');
        }
        ++output.height;
    }
    return output;
}

std::vector<int64_t> getAdjacentPositions(int64_t pos, int64_t width, int64_t height) {
    std::vector<int64_t> positions;
    int64_t x = pos % width;
    int64_t y = pos / width;
    if (x > 0) positions.push_back((x - 1l) + y * width);
    if (y > 0) positions.push_back(x + (y - 1l) * width);
    if (x < width - 1) positions.push_back((x + 1l) + y * width);
    if (y < height - 1) positions.push_back(x + (y + 1l) * width);
    return positions;
}

template<int64_t expansion>
int64_t getWeightAtPos(int64_t pos, const AoC::AoCDay<c_day>::input_t &input) {
    if (expansion == 1) return input.grid[pos];
    const int64_t eX = pos % (input.width * expansion);
    const int64_t eY = pos / (input.width * expansion);
    const int64_t trueX = eX % input.width;
    const int64_t trueY = eY % input.height;
    const int64_t offset = eX / input.width + eY / input.height;
    return (input.grid[trueX + trueY * input.width] + offset - 1) % 9 + 1;
}

template<int64_t expansion = 1>
AoC::day_result_t getShortestPath(const AoC::AoCDay<c_day>::input_t &input) {
    std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>, std::greater<std::pair<int64_t, int64_t>>>  priorityQueue;
    std::vector<int64_t> dist(input.width * input.height * expansion * expansion, INF);

    priorityQueue.push(std::make_pair(0, 0));
    dist[0] = 0;

    while (!priorityQueue.empty()) {
        const int64_t u = priorityQueue.top().second;
        priorityQueue.pop();
        for (const auto& v : getAdjacentPositions(u, input.width * expansion, input.height * expansion)) {
            const int64_t weight{getWeightAtPos<expansion>(v, input)};

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                priorityQueue.push(std::make_pair(dist[v], v));
            }
        }
    }
    return dist[dist.size() - 1];
}

AoC::day_result_t AoC::AoCDay<c_day>::runA(const input_t &input) {
    return getShortestPath(input);
}

AoC::day_result_t AoC::AoCDay<c_day>::runB(const input_t &input) {
    return getShortestPath<5>(input);
}
