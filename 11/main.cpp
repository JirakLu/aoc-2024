#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_map>


/*
*   If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
*   If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
*   If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
*/
std::vector<size_t> applyBlinkRules(size_t num) {
    if (num == 0) {
        return {1};
    }

    if (const int digits = static_cast<int>(std::floor(std::log10(num)) + 1); digits % 2 == 0) {
        const auto divisor = static_cast<size_t>(std::pow(10, digits / 2));
        size_t left = num / divisor;
        size_t right = num % divisor;
        return {left, right};
    }
    return {num * 2024};
}

std::unordered_map<size_t, size_t> applyBlinkRules2(size_t num, size_t count) {
    std::unordered_map<size_t, size_t> result;

    if (num == 0) {
        result[1] += count;
    } else {
        if (const int digits = static_cast<int>(std::floor(std::log10(num)) + 1); digits % 2 == 0) {
            const auto divisor = static_cast<size_t>(std::pow(10, digits / 2));
            const size_t left = num / divisor;
            const size_t right = num % divisor;
            result[left] += count;
            result[right] += count;
        } else {
            result[num * 2024] += count;
        }
    }

    return result;
}

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);
    std::vector<size_t> numbers;
    size_t num;
    while (file >> num) numbers.push_back(num);
    size_t BLINK_COUNT = 25;

    for (size_t i = 0; i < BLINK_COUNT; i++) {
        std::vector<size_t> temp;
        for (const auto &number: numbers) {
            auto nums = applyBlinkRules(number);
            temp.insert(temp.end(), nums.begin(), nums.end());
        }
        numbers = temp;
    }

    std::cout << numbers.size() << std::endl;
    file.close();
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    std::unordered_map<size_t, size_t> numbers;
    size_t num;
    while (file >> num) numbers[num]++;
    file.close();

    size_t BLINK_COUNT = 75;

    for (size_t i = 0; i < BLINK_COUNT; ++i) {
        std::unordered_map<size_t, size_t> nextNumbers;

        for (const auto &[number, count]: numbers) {
            auto results = applyBlinkRules2(number, count);
            for (const auto &[result, resultCount]: results) {
                nextNumbers[result] += resultCount;
            }
        }

        numbers = std::move(nextNumbers);
    }

    size_t totalCount = 0;
    for (const auto &[number, count]: numbers) {
        totalCount += count;
    }
    std::cout << totalCount << std::endl;
}

int main() {
    solution1("../11/input.txt");

    solution2("../11/input.txt");
}


