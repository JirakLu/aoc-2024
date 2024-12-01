#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);
    std::vector<int> left, right;

    int l, r;
    while (file >> l >> r) {
        left.push_back(l);
        right.push_back(r);
    }

    std::ranges::sort(left);
    std::ranges::sort(right);

    size_t acc = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        acc += std::abs(left[i] - right[i]);
    }
    std::cout << acc << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    std::vector<int> left;
    std::unordered_map<size_t, size_t> right;

    int l, r;
    while (file >> l >> r) {
        left.push_back(l);
        right[r] += 1;
    }

    std::ranges::sort(left);

    size_t acc = 0;
    for (const auto &item: left) {
        acc += item * right[item];
    }
    std::cout << acc << std::endl;
}

int main() {
    solution1("../01/input.txt");

    solution2("../01/input.txt");
}
