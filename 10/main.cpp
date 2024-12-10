#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <set>
#include <vector>

using Pos = std::pair<ssize_t, ssize_t>;

std::array<Pos, 4> directions = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

Pos operator+(const Pos &lhs, const Pos &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}


size_t countTrailHeads(const std::vector<std::vector<size_t>> &data, const Pos &pos) {
    using Vertex = Pos;
    size_t acc = 0;
    std::queue<Vertex> queue;
    std::set<Vertex> visited;
    queue.push(pos);
    visited.insert(pos);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        if (data[current.first][current.second] == 9) {
            acc++;
            continue;
        }

        for (const auto &dir: directions) {
            const auto newPos = current + dir;

            if (newPos.first < 0 || static_cast<size_t>(newPos.first) >= data.size() ||
                newPos.second < 0 || static_cast<size_t>(newPos.second) >= data[newPos.first].size()) {
                continue;
            }
            if (data[current.first][current.second] + 1 != data[newPos.first][newPos.second]) continue;
            if (visited.contains(newPos)) continue;

            queue.push(newPos);
            visited.insert(newPos);
        }
    }

    return acc;
}

size_t countAllTrailHeads(const std::vector<std::vector<size_t>> &data, const Pos &pos) {
    using Vertex = std::pair<Pos, std::set<Pos>>;
    size_t acc = 0;
    std::queue<Vertex> queue;
    queue.push({pos, {pos}});

    while (!queue.empty()) {
        auto current = queue.front().first;
        auto visited = queue.front().second;
        queue.pop();

        if (data[current.first][current.second] == 9) {
            acc++;
            continue;
        }

        for (const auto &dir: directions) {
            const auto newPos = current + dir;

            if (newPos.first < 0 || static_cast<size_t>(newPos.first) >= data.size() ||
                newPos.second < 0 || static_cast<size_t>(newPos.second) >= data[newPos.first].size()) {
                continue;
            }
            if (data[current.first][current.second] + 1 != data[newPos.first][newPos.second]) continue;


            if (visited.contains(newPos)) continue;

            visited.insert(newPos);
            queue.emplace(newPos, visited);
        }
    }

    return acc;
}

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::vector<std::vector<size_t>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<size_t> row;
        for (const auto &c: line) {
            row.push_back(c - '0');
        }
        data.push_back(row);
    }

    size_t acc = 0;
    for (size_t x = 0; x < data.size(); x++) {
        for (size_t y = 0; y < data[x].size(); y++) {
            if (data[x][y] != 0) continue;
            acc += countTrailHeads(data, {x, y});
        }
    }

    std::cout << acc << std::endl;
    file.close();
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    std::vector<std::vector<size_t>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<size_t> row;
        for (const auto &c: line) {
            row.push_back(c - '0');
        }
        data.push_back(row);
    }

    size_t acc = 0;
    for (size_t x = 0; x < data.size(); x++) {
        for (size_t y = 0; y < data[x].size(); y++) {
            if (data[x][y] != 0) continue;
            acc += countAllTrailHeads(data, {x, y});
        }
    }

    std::cout << acc << std::endl;

    file.close();
}

int main() {
    solution1("../10/input.txt");

    solution2("../10/input.txt");
}
