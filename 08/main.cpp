#include <fstream>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

using Pos = std::pair<ssize_t, ssize_t>;

struct PosHash {
    size_t m_Width;
    size_t m_Height;

    PosHash(const size_t width, const size_t height) : m_Width(width), m_Height(height) {
    }

    size_t operator()(const Pos &pos) const {
        return pos.first * m_Height + pos.second;
    }
};

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    size_t x = 0, y = 0;
    std::unordered_map<char, std::vector<Pos>> antennas;
    std::string line;
    while (std::getline(file, line)) {
        y = 0;
        for (char c: line) {
            if (c != '.') {
                antennas[c].emplace_back(x, y);
            }
            y++;
        }
        y = line.size();
        x++;
    }
    std::unordered_set<Pos, PosHash> antinodes(0, PosHash(x, y));

    for (const auto &positions: antennas | std::views::values) {
        for (size_t i = 0; i < positions.size(); ++i) {
            for (size_t j = i + 1; j < positions.size(); ++j) {
                const auto &pos1 = positions[i];
                const auto &pos2 = positions[j];

                size_t dx = pos1.first - pos2.first;
                size_t dy = pos1.second - pos2.second;

                Pos a1 = {pos1.first + dx, pos1.second + dy};
                Pos a2 = {pos2.first - dx, pos2.second - dy};

                if (a1.first >= 0 && static_cast<size_t>(a1.first) < x && a1.second >= 0 && static_cast<size_t>(a1.
                        second) < y) {
                    antinodes.insert(a1);
                }
                if (a2.first >= 0 && static_cast<size_t>(a2.first) < x && a2.second >= 0 && static_cast<size_t>(
                        a2.second) < y) {
                    antinodes.insert(a2);
                }
            }
        }
    }

    std::cout << antinodes.size() << std::endl;
    file.close();
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    size_t x = 0, y = 0;
    std::unordered_map<char, std::vector<Pos>> antennas;
    std::string line;
    while (std::getline(file, line)) {
        y = 0;
        for (char c: line) {
            if (c != '.') {
                antennas[c].emplace_back(x, y);
            }
            y++;
        }
        y = line.size();
        x++;
    }
    std::unordered_set<Pos, PosHash> antinodes(0, PosHash(x, y));

    for (const auto &positions: antennas | std::views::values) {
        for (size_t i = 0; i < positions.size(); ++i) {
            for (size_t j = i + 1; j < positions.size(); ++j) {
                const auto &pos1 = positions[i];
                const auto &pos2 = positions[j];

                size_t dx = pos1.first - pos2.first;
                size_t dy = pos1.second - pos2.second;

                ssize_t multiplier = 0;
                while (true) {
                    Pos a = {pos1.first + multiplier * dx, pos1.second + multiplier * dy};
                    if (a.first >= 0 && static_cast<size_t>(a.first) < x && a.second >= 0 && static_cast<size_t>(a.
                            second) < y) {
                        antinodes.insert(a);
                    } else {
                        break;
                    }
                    multiplier++;
                }

                multiplier = 0;
                while (true) {
                    Pos a = {pos1.first - multiplier * dx, pos1.second - multiplier * dy};
                    if (a.first >= 0 && static_cast<size_t>(a.first) < x && a.second >= 0 && static_cast<size_t>(a.
                            second) < y) {
                        antinodes.insert(a);
                    } else {
                        break;
                    }
                    multiplier++;
                }
            }
        }
    }

    std::cout << antinodes.size() << std::endl;
    file.close();
}

int main() {
    solution1("../08/input.txt");

    solution2("../08/input.txt");
}
