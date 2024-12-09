#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <ranges>
#include <vector>

struct Block {
    size_t m_Size;
    size_t m_Id;
    bool isMoved = false;
};

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::vector<size_t> line;
    char c = '0';
    size_t id = 0;
    size_t charCount = 0;
    bool isFile = true;
    while (file >> c) {
        const size_t count = c - '0';
        for (size_t i = 0; i < count; ++i) {
            if (isFile) {
                line.push_back(id);
                charCount++;
            } else {
                line.push_back(std::numeric_limits<size_t>::max());
            }
        }
        if (isFile) id++;
        isFile = !isFile;
    }

    size_t endIdx = line.size() - 1;
    for (size_t i = 0; i < charCount; ++i) {
        while (line[endIdx] == std::numeric_limits<size_t>::max()) {
            endIdx--;
        }
        if (line[i] == std::numeric_limits<size_t>::max()) {
            line[i] = line[endIdx--];
        }
    }

    size_t hash = 0;
    for (size_t i = 0; i < charCount; ++i) {
        hash += line[i] * i;
    }
    std::cout << hash << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    std::list<Block> blocks;
    char c = '0';
    size_t id = 0;
    bool isFile = true;
    while (file >> c) {
        const size_t count = c - '0';
        if (isFile) {
            blocks.emplace_back(count, id);
        } else {
            blocks.emplace_back(count, std::numeric_limits<size_t>::max());
        }
        if (isFile) id++;
        isFile = !isFile;
    }

    std::list<Block> result;

    for (auto &b: blocks) {
        if (b.m_Id != std::numeric_limits<size_t>::max() && !b.isMoved) {
            result.push_back(b);
            b.isMoved = true;
        } else {
            size_t size = b.m_Size;
            for (auto &block: std::ranges::reverse_view(blocks)) {
                if (block.m_Size <= size && !block.isMoved && block.m_Id != std::numeric_limits<size_t>::max()) {
                    result.push_back(block);
                    block.isMoved = true;
                    size -= block.m_Size;
                }
                if (size == 0) break;
            }

            if (size != 0) {
                result.emplace_back(size, std::numeric_limits<size_t>::max());
            }
        }
    }

    size_t hash = 0;
    size_t i = 0;
    for (auto &b: result) {
        for (size_t j = 0; j < b.m_Size; ++j) {
            if (b.m_Id != std::numeric_limits<size_t>::max()) {
                hash += b.m_Id * i;
            }
            i++;
        }
    }

    std::cout << hash << std::endl;
    file.close();
}

int main() {
    solution1("../09/input.txt");

    solution2("../09/input.txt");
}
