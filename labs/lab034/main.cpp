#include <iostream>
#include <random>

enum class Hand {
    Rock = 0,
    Scissors = 1,
    Paper = 2
};

const char* hand_to_text(Hand hand) {
    switch (hand) {
        case Hand::Rock:
            return "묵";
        case Hand::Scissors:
            return "찌";
        case Hand::Paper:
            return "빠";
    }

    return "?";
}

int main() {
    int player_code;
    std::cin >> player_code;

    std::mt19937 rng(20260324u);
    const Hand computer = static_cast<Hand>(rng() % 3);
    const Hand player = static_cast<Hand>(player_code);

    std::cout << "컴퓨터: " << hand_to_text(computer) << '\n';
    std::cout << "플레이어: " << hand_to_text(player) << '\n';

    switch (computer) {
        case Hand::Rock:
            switch (player) {
                case Hand::Rock:
                    std::cout << "결과: 비김";
                    break;
                case Hand::Scissors:
                    std::cout << "결과: 컴퓨터 승";
                    break;
                case Hand::Paper:
                    std::cout << "결과: 플레이어 승";
                    break;
            }
            break;

        case Hand::Scissors:
            switch (player) {
                case Hand::Rock:
                    std::cout << "결과: 플레이어 승";
                    break;
                case Hand::Scissors:
                    std::cout << "결과: 비김";
                    break;
                case Hand::Paper:
                    std::cout << "결과: 컴퓨터 승";
                    break;
            }
            break;

        case Hand::Paper:
            switch (player) {
                case Hand::Rock:
                    std::cout << "결과: 컴퓨터 승";
                    break;
                case Hand::Scissors:
                    std::cout << "결과: 플레이어 승";
                    break;
                case Hand::Paper:
                    std::cout << "결과: 비김";
                    break;
            }
            break;
    }

    return 0;
}