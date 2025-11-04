#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_{white}, black_{black} {

    auto in_range = [](int v) { return v >= 0 && v < 8; };

    if (!in_range(white.first) || !in_range(white.second) ||
        !in_range(black.first) || !in_range(black.second)) {
        throw std::domain_error("Queen position out of range");
    }

    if (white == black) {
        throw std::domain_error("Queens cannot share the same position");
    }
}

std::pair<int,int> chess_board::white() const {
    return white_;
}

std::pair<int,int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // same row  (compare row index, the second coordinate)
    if (white_.second == black_.second) return true;
    // same column (compare column index, the first coordinate)
    if (white_.first == black_.first) return true;
    // same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::string board;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (white_ == std::pair<int,int>{c, r}) {
                board += 'W';
            } else if (black_ == std::pair<int,int>{c, r}) {
                board += 'B';
            } else {
                board += '_';
            }
            if (c != 7) board += ' ';
        }
        board += '\n';
    }
    return board;
}

}  // namespace queen_attack
