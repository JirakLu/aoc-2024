#include <fstream>
#include <unordered_map>
#include <iostream>
#include <vector>

enum State {
    START,
    X,
    XM,
    XMA,
    S,
    SA,
    SAM,
    FAILED,
    FINAL
};

struct DFA {
    std::unordered_map<State, std::unordered_map<char, State>> m_Transitions;
    State m_InitialState = START;
    State m_FinalState = FINAL;

    DFA() {
        m_Transitions[START]['X'] = X;
        m_Transitions[X]['M'] = XM;
        m_Transitions[XM]['A'] = XMA;
        m_Transitions[XMA]['S'] = FINAL;

        m_Transitions[START]['S'] = S;
        m_Transitions[S]['A'] = SA;
        m_Transitions[SA]['M'] = SAM;
        m_Transitions[SAM]['X'] = FINAL;
    }

    State nextState(const State currentState, const char inputChar) const {
        if (m_Transitions.contains(currentState)) {
            if (m_Transitions.at(currentState).contains(inputChar))
                return m_Transitions.at(currentState).at(inputChar);
        }
        return FAILED;
    }
};

size_t countMatches(const std::string &line, const DFA &dfa) {
    State currentState = dfa.m_InitialState;
    size_t acc = 0;

    for (const auto &ch: line) {
        State nextState = dfa.nextState(currentState != FAILED ? currentState : dfa.m_InitialState, ch);

        switch (nextState) {
            case FINAL:
                acc++;
                currentState = dfa.nextState(dfa.m_InitialState, ch);
                continue;
            case FAILED:
                currentState = dfa.nextState(dfa.m_InitialState, ch);
                continue;
            default:
                break;
        }

        currentState = nextState;
    }

    return acc;
}

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string line;
    size_t acc = 0;
    std::vector<std::string> puzzle;

    while (std::getline(file, line)) {
        puzzle.push_back(line);
    }

    DFA dfa;
    for (const auto &vertical: puzzle) {
        acc += countMatches(vertical, dfa);
    }

    for (size_t i = 0; i < puzzle[0].size(); i++) {
        std::string horizontal;
        for (auto &j: puzzle) {
            horizontal += j[i];
        }
        acc += countMatches(horizontal, dfa);
    }

    size_t dim = puzzle.size();
    for (size_t k = 0; k < dim * 2 - 1; k++) {
        std::string diagonal;
        for (size_t j = 0; j <= k; j++) {
            size_t i = k - j;
            if (i < dim && j < dim) {
                diagonal += puzzle[i][j];
            }
        }
        acc += countMatches(diagonal, dfa);

        diagonal.clear();
        for (size_t j = 0; j <= k; j++) {
            size_t i = dim - 1 - k + j;
            if (i < dim && j < dim) {
                diagonal += puzzle[i][j];
            }
        }
        acc += countMatches(diagonal, dfa);
    }

    std::cout << acc << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::vector<char>> puzzle;

    while (std::getline(file, line)) {
        puzzle.emplace_back(line.begin(), line.end());
    }

    size_t acc = 0;
    for (size_t i = 1; i < puzzle.size() - 1; i++) {
        for (size_t j = 1; j < puzzle[i].size(); j++) {
            bool isA = puzzle[i][j] == 'A';
            bool isDiagonalFromLeft = (puzzle[i - 1][j - 1] == 'M' && puzzle[i + 1][j + 1] == 'S') || (
                                          puzzle[i - 1][j - 1] == 'S' && puzzle[i + 1][j + 1] == 'M');
            bool isDiagonalFromRight = (puzzle[i + 1][j - 1] == 'M' && puzzle[i - 1][j + 1] == 'S') || (
                                           puzzle[i + 1][j - 1] == 'S' && puzzle[i - 1][j + 1] == 'M');
            if (isA && isDiagonalFromLeft && isDiagonalFromRight) acc++;
        }
    }

    std::cout << acc << std::endl;
}

int main() {
    solution1("../04/input.txt");

    solution2("../04/input.txt");
}
