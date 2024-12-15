#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

using Grid = std::vector<std::vector<char>>;
using Pos = std::pair<ssize_t, ssize_t>;

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    Grid grid;
    std::vector<char> directions;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::vector<char> row;
        for (const auto &cell: line) {
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    while (std::getline(file, line)) {
        for (const auto &cell: line) {
            directions.push_back(cell);
        }
    }

    Pos start;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                start = {i, j};
                break;
            }
        }
    }

    std::unordered_map<char, Pos> rules = {{'^', {-1, 0}}, {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}};
    for (const auto &dir: directions) {
        Pos oldPos = start;
        Pos nextPos = {start.first + rules[dir].first, start.second + rules[dir].second};

        if (grid[nextPos.first][nextPos.second] == '#') continue;

        std::vector<Pos> blocks;
        Pos currentPos = nextPos;
        while (grid[currentPos.first][currentPos.second] == 'O') {
            blocks.push_back(currentPos);
            currentPos = {currentPos.first + rules[dir].first, currentPos.second + rules[dir].second};
        }
        if (grid[currentPos.first][currentPos.second] == '#') continue;

        std::reverse(blocks.begin(), blocks.end());
        for (const auto &block: blocks) {
            Pos nextBlock = {block.first + rules[dir].first, block.second + rules[dir].second};
            grid[block.first][block.second] = '.';
            grid[nextBlock.first][nextBlock.second] = 'O';
        }

        grid[oldPos.first][oldPos.second] = '.';
        grid[nextPos.first][nextPos.second] = '@';
        start = nextPos;
    }

    size_t acc = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                acc += 100 * i + j;
            };
        }
    }

    std::cout << acc << std::endl;
    file.close();
}

void solution2(const std::string &fileName) {
    std::ifstream file(fileName);


    Grid grid;
    std::vector<char> directions;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::vector<char> row;
        for (const auto &cell: line) {
            if (cell == '#') {
                row.push_back('#');
                row.push_back('#');
            } else if (cell == 'O') {
                row.push_back('[');
                row.push_back(']');
            } else if (cell == '.') {
                row.push_back('.');
                row.push_back('.');
            } else if (cell == '@') {
                row.push_back('@');
                row.push_back('.');
            }
        }
        grid.push_back(row);
    }

    while (std::getline(file, line)) {
        for (const auto &cell: line) {
            directions.push_back(cell);
        }
    }

    Pos start;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                start = {i, j};
                break;
            }
        }
    }

    std::unordered_map<char, Pos> rules = {{'^', {-1, 0}}, {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}};
    for (const auto &dir: directions) {
        Pos oldPos = start;
        Pos nextPos = {start.first + rules[dir].first, start.second + rules[dir].second};

        if (grid[nextPos.first][nextPos.second] == '#') continue;

        std::set<std::pair<Pos, char>> blocks;
        std::queue<Pos> blockQ;
        std::set<Pos> visited;
        blockQ.push(nextPos);
        while (!blockQ.empty()) {
            const auto currPos = blockQ.front();
            blockQ.pop();
            if (visited.contains(currPos)) continue;

            const auto current = grid[currPos.first][currPos.second];
            if (current != '[' && current != ']')
                continue;;

            if (current == '[') {
                blocks.emplace(currPos, '[');
                blocks.emplace(std::make_pair(currPos.first, currPos.second + 1), ']');
                blockQ.emplace(currPos.first + rules[dir].first, currPos.second + rules[dir].second);
                blockQ.emplace(currPos.first + rules[dir].first, currPos.second + 1 + rules[dir].second);
            } else {
                blocks.emplace(currPos, ']');
                blocks.emplace(std::make_pair(currPos.first, currPos.second - 1), '[');
                blockQ.emplace(currPos.first + rules[dir].first, currPos.second + rules[dir].second);
                blockQ.emplace(currPos.first + rules[dir].first, currPos.second - 1 + rules[dir].second);
            }

            visited.insert(currPos);
        }


        bool isValid = true;
        for (const auto &block: blocks) {
            Pos nextP = {block.first.first + rules[dir].first, block.first.second + rules[dir].second};
            if (grid[nextP.first][nextP.second] == '#') {
                isValid = false;
                break;
            }
        }
        if (!isValid) continue;


        for (const auto &block: blocks) {
            grid[block.first.first][block.first.second] = '.';
        }

        for (const auto &block: blocks) {
            Pos nextBlock = {block.first.first + rules[dir].first, block.first.second + rules[dir].second};
            grid[nextBlock.first][nextBlock.second] = block.second;
        }

        grid[oldPos.first][oldPos.second] = '.';
        grid[nextPos.first][nextPos.second] = '@';
        start = nextPos;
    }

    size_t acc = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '[') {
                acc += 100 * i + j;
            };
        }
    }

    std::cout << acc << std::endl;
    file.close();
}

int main() {
    solution1("../15/input.txt");

    solution2("../15/input.txt");
}


