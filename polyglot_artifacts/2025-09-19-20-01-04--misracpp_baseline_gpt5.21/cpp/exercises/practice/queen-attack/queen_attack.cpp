#include "queen_attack.h"
#include <stdexcept>
#include <cstdlib>  // for std::abs

namespace queen_attack {

chess_board::chess_board(chess_board::position white, chess_board::position black)
    : white_{white}, black_{black} {
    // Validate positions are on the board (0..7 for both row and column)
    auto in_bounds = [](int v) { return v >= 0 && v < 8; };
    if (!in_bounds(white_.first) || !in_bounds(white_.second) ||
        !in_bounds(black_.first) || !in_bounds(black_.second)) {
        throw std::domain_error("Queen positions must be on the board");
    }

    // Queens cannot occupy the same square
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

chess_board::position chess_board::white() const noexcept {
    return white_;
}

chess_board::position chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    // Same row or same column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    // Same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::string result;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            char cell = '_';
            if (white_ == chess_board::position{r, c}) cell = 'W';
            if (black_ == chess_board::position{r, c}) cell = 'B';
            result.push_back(cell);
            if (c < 7) result.push_back(' ');
        }
        if (r < 7) result.push_back('\n');
    }
    return result;
}

}  // namespace queen_attack
