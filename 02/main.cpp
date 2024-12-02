#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


bool isSequenceValid(const std::vector<int> &numbers) {
    bool inc = true, desc = true;

    for (size_t i = 1; i < numbers.size(); ++i) {
        int diff = numbers[i] - numbers[i - 1];

        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }

        if (diff > 0) inc = false;
        if (diff < 0) desc = false;
    }

    return inc || desc;
}

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string line;
    size_t count = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::vector<int> numbers;
        int n;
        while (ss >> n) {
            numbers.push_back(n);
        }

        if (isSequenceValid(numbers)) count++;
    }
    std::cout << count << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string line;
    size_t count = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::vector<int> numbers;
        int n;
        while (ss >> n) {
            numbers.push_back(n);
        }

        bool isValid = isSequenceValid(numbers);
        if (isValid) {
            count++;
            continue;
        }

        for (size_t i = 0; i < numbers.size(); ++i) {
            int ith = numbers[i];
            numbers.erase(numbers.begin() + i);
            if (isSequenceValid(numbers)) {
                isValid = true;
                break;
            }
            numbers.insert(numbers.begin() + i, ith);
        }

        if (isValid) count++;
    }
    std::cout << count << std::endl;
}

int main() {
    solution1("../02/input.txt");

    solution2("../02/input.txt");
}
