#include <fstream>
#include <iostream>
#include <ranges>
#include <cmath>

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string line;
    size_t acc = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        const double aX = std::stoi(line.substr(line.find('X') + 2, line.find(',') - line.find('X') - 1));
        const double aY = std::stoi(line.substr(line.find('Y') + 2, line.find('\n') - line.find('Y') - 1));
        std::getline(file, line);
        const double bX = std::stoi(line.substr(line.find('X') + 2, line.find(',') - line.find('X') - 1));
        const double bY = std::stoi(line.substr(line.find('Y') + 2, line.find('\n') - line.find('Y') - 1));
        std::getline(file, line);
        const double aTarget = std::stoi(line.substr(line.find('X') + 2, line.find(',') - line.find('X') - 1));
        const double bTarget = std::stoi(line.substr(line.find('Y') + 2, line.find('\n') - line.find('Y') - 1));

        double y = (aTarget * aY - aX * bTarget) / (bX * aY - aX * bY);
        double x = (aTarget - bX * y) / aX;


        if (x <= 100 && y <= 100 && x > 0 && y > 0 && std::floor(x) == x && std::floor(y) == y) {
            acc += x * 3 + y;
        }
    }

    std::cout << acc << std::endl;
    file.close();
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string line;
    size_t acc = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        const long double aX = std::stoi(line.substr(line.find('X') + 2, line.find(',') - line.find('X') - 1));
        const long double aY = std::stoi(line.substr(line.find('Y') + 2, line.find('\n') - line.find('Y') - 1));
        std::getline(file, line);
        const long double bX = std::stoi(line.substr(line.find('X') + 2, line.find(',') - line.find('X') - 1));
        const long double bY = std::stoi(line.substr(line.find('Y') + 2, line.find('\n') - line.find('Y') - 1));
        std::getline(file, line);
        long double aTarget = std::stoi(line.substr(line.find('X') + 2, line.find(',') - line.find('X') - 1));
        long double bTarget = std::stoi(line.substr(line.find('Y') + 2, line.find('\n') - line.find('Y') - 1));
        aTarget += 10000000000000;
        bTarget += 10000000000000;


        long double y = (aTarget * aY - aX * bTarget) / (bX * aY - aX * bY);
        long double x = (aTarget - bX * y) / aX;


        if (x > 0 && y > 0 && std::floor(x) == x && std::floor(y) == y) {
            acc += x * 3 + y;
        }
    }

    std::cout << acc << std::endl;
    file.close();
}

int main() {
    solution1("../13/input.txt");

    solution2("../13/input.txt");
}


