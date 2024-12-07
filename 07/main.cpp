#include <fstream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

struct Equation {
    enum Operations {
        ADDITION = '+',
        MULTIPLICATION = '*',
        CONCATENATION = '|'
    };

    Equation(const size_t left, std::vector<size_t> right): m_Left(left), m_Right(std::move(right)) {
    };

    size_t solutionCount(std::vector<Operations> operations) {
        return std::accumulate(operations.begin(), operations.end(), 0,
                               [this,&operations](const auto &acc, const auto &op) {
                                   return acc + countSolutions(0, 0, op, operations);
                               });
    }

private:
    size_t m_Left = 0;
    std::vector<size_t> m_Right;

    size_t countSolutions(const size_t index, const size_t current, const char lastOp,
                          const std::vector<Operations> &operations) {
        if (index == m_Right.size()) return current == m_Left ? 1 : 0;
        if (current > m_Left) return 0;

        size_t count = 0;
        const size_t next = m_Right[index];

        count += std::accumulate(operations.begin(), operations.end(), 0,
                                 [this, &index, &current, &next, &lastOp, &operations
                                 ](const auto &acc, const auto &op) {
                                     size_t nextNum;
                                     switch (lastOp) {
                                         case ADDITION:
                                             nextNum = current + next;
                                             break;
                                         case MULTIPLICATION:
                                             nextNum = current * next;
                                             break;
                                         case CONCATENATION:
                                             nextNum = concatenate(current, next);
                                             break;
                                         default:
                                             throw std::runtime_error("Invalid operation");
                                     }
                                     return acc + countSolutions(index + 1, nextNum, op, operations);
                                 });

        return count;
    }

    static size_t concatenate(size_t a, size_t b) {
        std::string str = std::to_string(a) + std::to_string(b);
        return std::stoull(str);
    }
};

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);
    size_t acc = 0;

    std::string line;
    while (std::getline(file, line)) {
        size_t left;
        char c;
        std::vector<size_t> right;

        std::istringstream iss(line);
        iss >> left >> c;
        if (c != ':') throw std::runtime_error("Invalid input");

        size_t tmp;
        while (iss >> tmp) {
            right.push_back(tmp);
        }

        Equation eq(left, right);
        if (eq.solutionCount({Equation::Operations::ADDITION, Equation::Operations::MULTIPLICATION}) > 0) {
            acc += left;
        }
    }

    std::cout << acc << std::endl;
    file.close();
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    size_t acc = 0;

    std::string line;
    while (std::getline(file, line)) {
        size_t left;
        char c;
        std::vector<size_t> right;

        std::istringstream iss(line);
        iss >> left >> c;
        if (c != ':') throw std::runtime_error("Invalid input");

        size_t tmp;
        while (iss >> tmp) {
            right.push_back(tmp);
        }

        Equation eq(left, right);
        if (eq.solutionCount({
                Equation::Operations::ADDITION, Equation::Operations::MULTIPLICATION,
                Equation::Operations::CONCATENATION
            }) > 0) {
            acc += left;
        }
    }

    std::cout << acc << std::endl;
    file.close();
}

int main() {
    solution1("../07/input.txt");

    solution2("../07/input.txt");
}
