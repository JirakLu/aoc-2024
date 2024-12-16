#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

using Grid = std::vector<std::vector<char>>;
using Pos = std::pair<ssize_t, ssize_t>;
using Dir = std::pair<ssize_t, ssize_t>;

std::ostream &operator<<(std::ostream &os, const Pos &pos) {
    os << "[ " << pos.first << ", " << pos.second << " ]";
    return os;
}

struct Vertex {
    Pos m_Pos;
    size_t m_Cost;
    Dir m_Dir;
    std::set<Pos> m_Path;

    friend auto operator<(const Vertex &lhs, const Vertex &rhs) {
        return lhs.m_Cost > rhs.m_Cost;
    }
};

std::array<Dir, 4> directions = {
    {
        Dir{0, 1},
        Dir{-1, 0},
        Dir{0, -1},
        Dir{1, 0}
    }
};

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    Grid grid;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::vector<char> row;
        for (const auto &cell: line) {
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    size_t n = grid.size();
    size_t m = grid[0].size();
    Pos start, end;

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') {
                start = {i, j};
                grid[i][j] = '.';
            }
            if (grid[i][j] == 'E') {
                end = {i, j};
                grid[i][j] = '.';
            }
        }
    }

    std::map<Pos, size_t> d;
    std::priority_queue<Vertex> q;
    q.push({start, 0, {0, 1}, {}});

    while (!q.empty()) {
        const auto curr = q.top();
        q.pop();

        if (curr.m_Pos == end) {
            std::cout << curr.m_Cost << std::endl;
            break;
        }


        for (const auto &dir: directions) {
            if (dir.first == -curr.m_Dir.first && dir.second == -curr.m_Dir.second) continue;
            Pos newPos = {curr.m_Pos.first + dir.first, curr.m_Pos.second + dir.second};

            if (newPos.first < 0 || static_cast<size_t>(newPos.first) >= n ||
                newPos.second < 0 || static_cast<size_t>(newPos.second) >= m) {
                continue;
            }

            if (grid[newPos.first][newPos.second] == '#') {
                continue;
            }

            size_t newCost = curr.m_Cost + 1 + (dir == curr.m_Dir ? 0 : 1) * 1000;
            if (!d.contains(newPos) || newCost < d[newPos]) {
                d[newPos] = newCost;
                q.push({newPos, newCost, dir, {}});
            }
        }
    }

    file.close();
}

void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    Grid grid;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::vector<char> row;
        for (const auto &cell: line) {
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    size_t n = grid.size();
    size_t m = grid[0].size();
    Pos start, end;

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') {
                start = {i, j};
                grid[i][j] = '.';
            }
            if (grid[i][j] == 'E') {
                end = {i, j};
                grid[i][j] = '.';
            }
        }
    }

    std::map<Pos, size_t> d;
    std::priority_queue<Vertex> q;
    q.push({start, 0, {0, 1}, {start}});
    size_t minCost = std::numeric_limits<size_t>::max();
    std::set<Pos> paths;

    while (!q.empty()) {
        const auto curr = q.top();
        q.pop();

        if (curr.m_Pos == end) {
            if (curr.m_Cost > minCost) break;
            if (curr.m_Cost < minCost) minCost = curr.m_Cost;
            for (const auto &pos: curr.m_Path) {
                paths.insert(pos);
            }
            continue;
        }


        for (const auto &dir: directions) {
            if (dir.first == -curr.m_Dir.first && dir.second == -curr.m_Dir.second) continue;
            Pos newPos = {curr.m_Pos.first + dir.first, curr.m_Pos.second + dir.second};

            if (newPos.first < 0 || static_cast<size_t>(newPos.first) >= n ||
                newPos.second < 0 || static_cast<size_t>(newPos.second) >= m) {
                continue;
            }

            if (grid[newPos.first][newPos.second] == '#') {
                continue;
            }

            size_t newCost = curr.m_Cost + 1 + (dir == curr.m_Dir ? 0 : 1) * 1000;
            if (!d.contains(newPos) || newCost <= d[newPos] + 1000) {
                d[newPos] = newCost;
                std::set<Pos> newPath = curr.m_Path;
                newPath.insert(newPos);

                q.push({newPos, newCost, dir, newPath});
            }
        }
    }

    std::cout << paths.size() << std::endl;
    file.close();
}

int main() {
    solution1("../16/input.txt");

    solution2("../16/input.txt");
}


