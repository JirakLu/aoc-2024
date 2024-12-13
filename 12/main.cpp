#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <cmath>
#include <map>
#include <queue>
#include <set>

struct Point {
    char m_C;
    bool m_Visited = false;
};

using Pos = std::pair<ssize_t, ssize_t>;
using Grid = std::vector<std::vector<Point>>;

std::array<Pos, 4> directions = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

Pos operator+(const Pos &lhs, const Pos &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

size_t countPlotPrice(Grid &grid, const Pos &start) {
    const char plot = grid[start.first][start.second].m_C;
    using Vertex = Pos;
    std::queue<Vertex> queue;
    std::set<Vertex> visited;
    size_t fences = 0;
    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();

        for (const auto &d: directions) {
            const auto newPos = curr + d;

            if (newPos.first < 0 || static_cast<size_t>(newPos.first) >= grid.size() ||
                newPos.second < 0 || static_cast<size_t>(newPos.second) >= grid[newPos.first].size() ||
                grid[newPos.first][newPos.second].m_C != plot) {
                fences++;
                continue;
            }

            if (visited.contains(newPos)) continue;

            grid[newPos.first][newPos.second].m_Visited = true;
            visited.insert(newPos);
            queue.push(newPos);
        }
    }

    return visited.size() * fences;
}


size_t countPlotPrice2(Grid &grid, const Pos &start) {
    const char plot = grid[start.first][start.second].m_C;
    using Vertex = Pos;
    std::queue<Vertex> queue;
    std::set<Vertex> visited;
    std::map<Pos, std::pair<ssize_t, bool>> fences;
    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();

        for (const auto &d: directions) {
            const auto newPos = curr + d;

            if (newPos.first < 0 || static_cast<size_t>(newPos.first) >= grid.size() ||
                newPos.second < 0 || static_cast<size_t>(newPos.second) >= grid[newPos.first].size() ||
                grid[newPos.first][newPos.second].m_C != plot) {
                fences[newPos].first++;
                continue;
            }

            if (visited.contains(newPos)) continue;

            grid[newPos.first][newPos.second].m_Visited = true;
            visited.insert(newPos);
            queue.push(newPos);
        }
    }

    bool found = true;
    while (found) {
        found = false;
        for (const auto &[fence, count]: fences) {
            if (count.second) continue;
            if (count.first == 3) {
                fences[fence].second = true;
                for (const auto &d: directions) {
                    auto newPos = fence + d;

                    while (fences.contains(newPos) && !fences[newPos].second) {
                        found = true;
                        fences[newPos].first -= 2;
                        fences[newPos].second = true;
                        newPos = newPos + d;
                    }
                }
            }
        }
    }

    found = true;
    while (found) {
        found = false;
        for (const auto &[fence, count]: fences) {
            if (count.second) continue;
            if (count.first == 2) {
                fences[fence].second = true;
                for (const auto &d: directions) {
                    auto newPos = fence + d;

                    while (fences.contains(newPos) && !fences[newPos].second) {
                        found = true;
                        fences[newPos].first--;
                        fences[newPos].second = true;
                        newPos = newPos + d;
                    }
                }
            }
        }
    }

    found = true;
    while (found) {
        found = false;
        for (const auto &[fence, count]: fences) {
            if (count.second) continue;
            if (count.first == 1) {
                fences[fence].second = true;
                for (const auto &d: directions) {
                    auto newPos = fence + d;

                    while (fences.contains(newPos) && !fences[newPos].second) {
                        found = true;
                        fences[newPos].second = true;
                        fences[newPos].first--;
                        newPos = newPos + d;
                    }
                }
            }
        }
    }


    size_t res = 0;

    for (const auto &[fence, count]: fences) {
        if (count.first > 0) res += count.first;
    }

    return visited.size() * res;
}


void solution1(const std::string &fileName) {
    std::ifstream file(fileName);
    Grid grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.emplace_back(line.begin(), line.end());
    }
    file.close();

    std::set<char> visitedPlots;
    size_t acc = 0;

    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j].m_Visited) continue;
            acc += countPlotPrice(grid, {i, j});
        }
    }

    std::cout << acc << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    Grid grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.emplace_back(line.begin(), line.end());
    }
    file.close();

    std::set<char> visitedPlots;
    size_t acc = 0;

    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j].m_Visited) continue;
            acc += countPlotPrice2(grid, {i, j});
        }
    }

    std::cout << acc << std::endl;
}

int main() {
    solution1("../12/input.txt");

    // TODO: fix should be 865662
    solution2("../12/input.txt");
}


