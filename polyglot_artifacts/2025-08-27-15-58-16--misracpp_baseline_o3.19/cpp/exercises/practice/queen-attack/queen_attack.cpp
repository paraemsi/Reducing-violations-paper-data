#include "queen_attack.h"

#include <cmath>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos_{white}, black_pos_{black} {

    auto on_board = [](const std::pair<int, int>& pos) {
        return pos.first >= 0 && pos.first < 8 &&
               pos.second >= 0 && pos.second < 8;
    };

    if (!on_board(white) || !on_board(black) || white == black) {
        throw std::domain_error("Invalid queen position");
    }
}

const std::pair<int, int>& chess_board::white() const noexcept {
    return white_pos_;
}

const std::pair<int, int>& chess_board::black() const noexcept {
    return black_pos_;
}

bool chess_board::can_attack() const noexcept {
    // same row
    if (white_pos_.first == black_pos_.first) {
        return true;
    }
    // same column
    if (white_pos_.second == black_pos_.second) {
        return true;
    }
    // same diagonal
    return std::abs(white_pos_.first - black_pos_.first) ==
           std::abs(white_pos_.second - black_pos_.second);
}

}  // namespace queen_attack
