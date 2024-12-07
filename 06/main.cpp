#include <fstream>
#include <ranges>
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using Pos = std::pair<int, int>;

Pos operator+(const Pos &lhs, const Pos &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

Pos operator-(const Pos &lhs, const Pos &rhs) {
    return {lhs.first - rhs.first, lhs.second - rhs.second};
}

std::array<Pos, 4> directions = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::vector<std::vector<char>> map;
    std::string line;
    std::pair position = {-1, -1};
    while (std::getline(file, line)) {
        map.emplace_back(line.begin(), line.end());
        if (position.second == -1) {
            position.first++;

            if (auto it = std::ranges::find(line, '^'); it != line.end()) {
                position.second = static_cast<int>(std::distance(line.begin(), it));
            }
        }
    }
    if (position.second == -1) throw std::runtime_error("No starting position found");

    size_t acc = 0;
    size_t direction = 0;
    while (true) {
        if (map[position.first][position.second] != 'X') {
            map[position.first][position.second] = 'X';
            acc++;
        }

        auto next = position + directions[direction];

        if (next.first < 0 || next.first >= static_cast<int>(map.size()) || next.second < 0 || next.second >=
            static_cast<int>(map[0].size())) {
            break;
        }

        if (map[next.first][next.second] == '#') {
            direction = (direction + 1) % 4;
        } else {
            position = next;
        }
    }

    std::cout << acc << std::endl;
    file.close();
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    std::vector<std::vector<char>> map;
    std::string line;
    std::pair position = {-1, -1};
    while (std::getline(file, line)) {
        map.emplace_back(line.begin(), line.end());
        if (position.second == -1) {
            position.first++;

            if (auto it = std::ranges::find(line, '^'); it != line.end()) {
                position.second = static_cast<int>(std::distance(line.begin(), it));
            }
        }
    }
    if (position.second == -1) throw std::runtime_error("No starting position found");

    size_t direction = 0;
    std::set<Pos> blockages;
    blockages.insert(position);

    while (true) {
        auto next = position + directions[direction];

        if (next.first < 0 || next.first >= static_cast<int>(map.size()) || next.second < 0 || next.second >=
            static_cast<int>(map[0].size())) {
            break;
        }

        if (map[next.first][next.second] != '#' && !blockages.contains(next)) {
            auto tmp = map[next.first][next.second];
            map[next.first][next.second] = '#';

            std::set<std::pair<Pos, Pos>> visited;
            auto cycleDirection = direction;
            auto cyclePosition = position;

            while (true) {
                auto nextCyclePosition = cyclePosition + directions[cycleDirection];

                if (nextCyclePosition.first < 0 || nextCyclePosition.first >= static_cast<int>(map.size()) ||
                    nextCyclePosition.second < 0 || nextCyclePosition.second >= static_cast<int>(map[0].size())) {
                    break;
                }

                if (map[nextCyclePosition.first][nextCyclePosition.second] == '#') {
                    visited.insert({position, directions[direction]});
                    cycleDirection = (cycleDirection + 1) % 4;
                } else {
                    if (visited.contains({cyclePosition, directions[cycleDirection]})) {
                        blockages.insert(next);
                        break;
                    }
                    visited.insert({cyclePosition, directions[cycleDirection]});
                    cyclePosition = nextCyclePosition;
                }
            }

            map[next.first][next.second] = tmp;
        }

        if (map[next.first][next.second] == '#') {
            direction = (direction + 1) % 4;
        } else {
            position = next;
        }
    }

    std::cout << blockages.size() - 1 << std::endl;
    file.close();
}

int main() {
    solution1("../06/input.txt");

    // TODO: fix should be 1789
    solution2("../06/input.txt");
}
