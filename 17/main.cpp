#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>


void solution1(const std::string &fileName) {
    std::ifstream file(fileName);
    std::array<size_t, 3> registers{};
    std::string line;
    std::getline(file, line);
    registers[0] = std::stoul(line.substr(12));
    std::getline(file, line);
    registers[1] = std::stoul(line.substr(12));
    std::getline(file, line);
    registers[2] = std::stoul(line.substr(12));
    std::getline(file, line);

    std::getline(file, line);
    line = line.substr(9);
    std::stringstream ss(line);
    std::vector<std::pair<size_t, size_t>> instructions;
    std::pair<size_t, size_t> instr;
    bool hasTwo = false;
    size_t num;
    char c;
    while (ss >> num) {
        if (hasTwo) {
            instr.second = num;
            instructions.push_back(instr);
            hasTwo = false;
        } else {
            instr.first = num;
            hasTwo = true;
        }
        ss >> c;
    }

    for (const auto &[opcode, operand]: instructions) {
        switch (opcode) {
            case 0: // adv

                break;
        }
    }

    file.close();
}

void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    file.close();
}

int main() {
    solution1("../17/test.txt");

    solution2("../17/test.txt");
}


