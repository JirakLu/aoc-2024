#include <fstream>
#include <unordered_map>
#include <iostream>

enum State {
    START,
    M,
    MU,
    MUL,
    OPEN_PAREN,
    FIRST_NUMBER,
    COMMA,
    SECOND_NUMBER,
    CLOSE_PAREN,
    FAILED,
    D,
    DO,
    DON,
    DONI,
    DONT,
    DO_OPEN_PAREN,
    DO_CLOSE_PAREN,
    DONT_OPEN_PAREN,
    DONT_CLOSE_PAREN,
    FINAL
};

struct DFA {
    std::unordered_map<State, std::unordered_map<char, State>> m_Transitions;
    State m_InitialState = START;
    State m_FinalState = FINAL;

    DFA() {
        m_Transitions[START]['m'] = M;
        m_Transitions[M]['u'] = MU;
        m_Transitions[MU]['l'] = MUL;
        m_Transitions[MUL]['('] = OPEN_PAREN;
        m_Transitions[FIRST_NUMBER][','] = COMMA;
        m_Transitions[SECOND_NUMBER][')'] = CLOSE_PAREN;

        for (char ch = '0'; ch <= '9'; ++ch) {
            m_Transitions[OPEN_PAREN][ch] = FIRST_NUMBER;
            m_Transitions[FIRST_NUMBER][ch] = FIRST_NUMBER;
            m_Transitions[SECOND_NUMBER][ch] = SECOND_NUMBER;
            m_Transitions[COMMA][ch] = SECOND_NUMBER;
        }

        // dont, do transitions
        m_Transitions[START]['d'] = D;
        m_Transitions[D]['o'] = DO;
        m_Transitions[DO]['n'] = DON;
        m_Transitions[DON]['\''] = DONI;
        m_Transitions[DONI]['t'] = DONT;
        m_Transitions[DONT]['('] = DONT_OPEN_PAREN;
        m_Transitions[DONT_OPEN_PAREN][')'] = DONT_CLOSE_PAREN;

        m_Transitions[DO]['('] = DO_OPEN_PAREN;
        m_Transitions[DO_OPEN_PAREN][')'] = DO_CLOSE_PAREN;
    }

    State nextState(const State currentState, const char inputChar) const {
        if (m_Transitions.contains(currentState)) {
            if (m_Transitions.at(currentState).contains(inputChar))
                return m_Transitions.at(currentState).at(inputChar);
        }
        return FAILED;
    }
};

void solution1(const std::string &fileName) {
    std::ifstream file(fileName);

    DFA dfa;
    State currentState = dfa.m_InitialState;
    std::string line;
    size_t left = 0, right = 0;
    size_t acc = 0;

    while (std::getline(file, line)) {
        for (const auto &ch: line) {
            State nextState = dfa.nextState(currentState != FAILED ? currentState : dfa.m_InitialState, ch);

            switch (nextState) {
                case FIRST_NUMBER:
                    left = left * 10 + (ch - '0');
                    break;
                case SECOND_NUMBER:
                    right = right * 10 + (ch - '0');
                    break;
                case CLOSE_PAREN:
                    acc += left * right;
                    left = right = 0;
                    break;
                case FAILED:
                    currentState = dfa.nextState(dfa.m_InitialState, ch);
                    left = right = 0;
                    continue;
                default:
                    break;
            }

            currentState = nextState;
        }
    }

    std::cout << acc << std::endl;
}


void solution2(const std::string &fileName) {
    std::ifstream file(fileName);

    DFA dfa;
    State currentState = dfa.m_InitialState;
    std::string line;
    size_t left = 0, right = 0;
    size_t acc = 0;
    bool isEnabled = true;

    while (std::getline(file, line)) {
        for (const auto &ch: line) {
            State nextState = dfa.nextState(currentState != FAILED ? currentState : dfa.m_InitialState, ch);

            switch (nextState) {
                case FIRST_NUMBER:
                    left = left * 10 + (ch - '0');
                    break;
                case SECOND_NUMBER:
                    right = right * 10 + (ch - '0');
                    break;
                case CLOSE_PAREN:
                    if (isEnabled)
                        acc += left * right;
                    left = right = 0;
                    break;
                case DONT_CLOSE_PAREN:
                    isEnabled = false;
                    break;
                case DO_CLOSE_PAREN:
                    isEnabled = true;
                    break;
                case FAILED:
                    currentState = dfa.nextState(dfa.m_InitialState, ch);
                    left = right = 0;
                    continue;
                default:
                    break;
            }

            currentState = nextState;
        }
    }

    std::cout << acc << std::endl;
}

int main() {
    solution1("../03/input.txt");

    solution2("../03/input.txt");
}
