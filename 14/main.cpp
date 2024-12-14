#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string line;
    size_t acc = 0;
    ssize_t WIDTH = 101, HEIGHT = 103, SECONDS = 100;
    std::tuple<size_t, size_t, size_t, size_t> quadrants = {0, 0, 0, 0};
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        char ignore;
        ssize_t px, py, vx, vy;

        ss >> ignore >> ignore >> px >> ignore >> py >> ignore >> ignore >> vx >> ignore >> vy;

        px = ((px + SECONDS * vx) % WIDTH + WIDTH) % WIDTH;
        py = ((py + SECONDS * vy) % HEIGHT + HEIGHT) % HEIGHT;

        if (px < WIDTH / 2 && py < HEIGHT / 2) {
            std::get<0>(quadrants)++;
        } else if (px > WIDTH / 2 && py < HEIGHT / 2) {
            std::get<1>(quadrants)++;
        } else if (px < WIDTH / 2 && py > HEIGHT / 2) {
            std::get<2>(quadrants)++;
        } else if (px > WIDTH / 2 && py > HEIGHT / 2) {
            std::get<3>(quadrants)++;
        }
    }

    acc = std::get<0>(quadrants) * std::get<1>(quadrants) * std::get<2>(quadrants) * std::get<3>(quadrants);

    std::cout << acc << std::endl;
    file.close();
}

struct Robot {
    Robot(ssize_t px, ssize_t py, ssize_t vx, ssize_t vy) : m_Position(px, py), m_Velocity(vx, vy) {
    }

    std::pair<ssize_t, ssize_t> m_Position;
    std::pair<ssize_t, ssize_t> m_Velocity;
};


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    std::vector<Robot> robots;
    std::string line;
    ssize_t WIDTH = 101, HEIGHT = 103;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        char ignore;
        ssize_t px, py, vx, vy;

        ss >> ignore >> ignore >> px >> ignore >> py >> ignore >> ignore >> vx >> ignore >> vy;
        robots.emplace_back(px, py, vx, vy);
    }

    size_t seconds = 1;
    while (true) {
        std::set<std::pair<ssize_t, ssize_t>> positions;
        for (auto &robot: robots) {
            robot.m_Position.first = ((robot.m_Position.first + robot.m_Velocity.first) % WIDTH + WIDTH) % WIDTH;
            robot.m_Position.second = ((robot.m_Position.second + robot.m_Velocity.second) % HEIGHT + HEIGHT) % HEIGHT;
            positions.insert(robot.m_Position);
        }

        if (positions.size() == robots.size()) {
            for (ssize_t y = 0; y < HEIGHT; y++) {
                for (ssize_t x = 0; x < WIDTH; x++) {
                    bool found = false;
                    for (auto &robot: robots) {
                        if (robot.m_Position.first == x && robot.m_Position.second == y) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        std::cout << "\u2588";
                    } else {
                        std::cout << " ";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << "Seconds: " << seconds << std::endl;
            break;
        }
        seconds++;
    }

    file.close();
}

int main() {
    solution1("../14/input.txt");

    solution2("../14/input.txt");
}


