#include <iostream>
#include <stack>
#include <map>
#include "Matrix.h"

namespace AoC {

    int traverse(const std::map<std::string, std::vector<std::string>>& adjacency, std::set<std::string>& visited, const std::string& current, bool doubleVisit) {
        bool isDoubleVisit{false};
        if (current == "end") return 1;
        // visited only contains small caves
        if (visited.contains(current)) {
            if (doubleVisit && current != "start") {
                isDoubleVisit = true;
            } else {
                return 0;
            }
        }
        if (islower(current[0])) visited.emplace(current);
        int paths{0};
        for (const auto& next : adjacency.at(current)) {
            paths += traverse(adjacency, visited, next, doubleVisit && !isDoubleVisit);
        }
        if (!isDoubleVisit) visited.erase(current);
        return paths;
    }

    int traverse(const std::map<std::string, std::vector<std::string>>& adjacency, bool doubleVisit = false) {
        std::set<std::string> visited;
        return traverse(adjacency, visited, "start", doubleVisit);
    }

    void day12(std::ifstream& file) {

        std::map<std::string, std::vector<std::string>> adjacency;

        std::string input;
        while (std::getline(file, input)) {
            std::stringstream inputStream{input};
            std::string left, right;
            std::getline(inputStream, left, '-');
            std::getline(inputStream, right, '-');

            if (adjacency.contains(left)) {
                adjacency[left].push_back(right);
            } else {
                adjacency[left] = {right};
            }

            if (adjacency.contains(right)) {
                adjacency[right].push_back(left);
            } else {
                adjacency[right] = {left};
            }
        }

        const auto paths = traverse(adjacency);
        const auto pathsDouble = traverse(adjacency, true);

        std::cout << "Paths: " << paths << std::endl;
        std::cout << "Paths with one double: " << pathsDouble << std::endl;
    }
}