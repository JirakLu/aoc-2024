#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);
    std::unordered_map<size_t, std::unordered_set<size_t>> rules;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::istringstream oss(line);
        char c;
        size_t left, right;
        oss >> left >> c >> right;
        if (c != '|') break;
        rules[right].insert(left);
    }

    size_t acc = 0;
    while (std::getline(file, line)) {
        std::vector<size_t> numbers;
        std::istringstream oss(line + ',');
        size_t number;
        char c;
        while (oss >> number >> c) {
            numbers.push_back(number);
        }

        bool isValid = true;
        for (size_t i = 0; i < numbers.size() - 1; ++i) {
            for (size_t j = i + 1; j < numbers.size(); ++j) {
                if (rules[numbers[i]].contains(numbers[j])) {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) {
            acc += numbers[numbers.size() / 2];
        }
    }

    std::cout << acc << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    std::unordered_map<size_t, std::unordered_set<size_t>> edges;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::istringstream oss(line);
        char c;
        size_t left, right;
        oss >> left >> c >> right;
        if (c != '|') break;
        edges[left].insert(right);
    }

    size_t acc = 0;
    while (std::getline(file, line)) {
        std::unordered_map<size_t, size_t> indegree;
        std::vector<size_t> numbers;
        std::istringstream oss(line + ',');
        size_t number;
        char c;
        while (oss >> number >> c) {
            numbers.push_back(number);
        }

        std::queue<size_t> queue;
        for (const auto &num: numbers) {
            indegree[num] = 0;
            for (const auto &[key, value]: edges) {
                if (value.contains(num) && std::ranges::find(numbers, key) != numbers.end()) {
                    indegree[num]++;
                }
            }
            if (indegree[num] == 0) {
                queue.push(num);
            }
        }

        std::vector<size_t> result;
        while (!queue.empty()) {
            size_t node = queue.front();
            queue.pop();
            result.push_back(node);
            for (const auto &neighbour: edges[node]) {
                indegree[neighbour]--;
                if (indegree[neighbour] == 0) {
                    queue.push(neighbour);
                }
            }
        }

        bool isSame = true;
        for (size_t i = 0; i < numbers.size(); ++i) {
            if (numbers[i] != result[i]) {
                isSame = false;
                break;
            }
        }

        if (result.size() == numbers.size() && !isSame) {
            acc += result[result.size() / 2];
        }
    }

    std::cout << acc << std::endl;
}

int main() {
    solution1("../05/input.txt");

    solution2("../05/input.txt");
}
