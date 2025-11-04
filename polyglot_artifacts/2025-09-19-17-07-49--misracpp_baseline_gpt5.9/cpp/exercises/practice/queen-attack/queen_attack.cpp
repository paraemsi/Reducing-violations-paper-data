#include "queen_attack.h"

#include <stdexcept>
#include <cmath>  // for std::abs

namespace queen_attack {

chess_board::chess_board()
    : white_{0, 3}, black_{7, 3} {}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {
    auto in_bounds = [](int v) { return v >= 0 && v < 8; };
    if (!in_bounds(white_.first) || !in_bounds(white_.second) ||
        !in_bounds(black_.first) || !in_bounds(black_.second)) {
        throw std::domain_error("Positions must be on the board (0..7).");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same position.");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_;
}

std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // same row or same column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    // same diagonal
    return std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

}  // namespace queen_attack
