#include "queen_attack.h"

#include <cmath>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_position_{white}, black_position_{black} {
    if (white.first < 0 || white.first >= 8 || white.second < 0 || white.second >= 8 ||
        black.first < 0 || black.first >= 8 || black.second < 0 || black.second >= 8) {
        throw std::domain_error("Queen position out of bounds.");
    }

    if (white_position_ == black_position_) {
        throw std::domain_error("Queens cannot be on the same square.");
    }
}

const std::pair<int, int>& chess_board::white() const {
    return white_position_;
}

const std::pair<int, int>& chess_board::black() const {
    return black_position_;
}

bool chess_board::can_attack() const {
    return white_position_.first == black_position_.first ||
           white_position_.second == black_position_.second ||
           std::abs(white_position_.first - black_position_.first) ==
               std::abs(white_position_.second - black_position_.second);
}

}  // namespace queen_attack
