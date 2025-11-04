#include "queen_attack.h"

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    auto in_bounds = [](int v) { return v >= 0 && v < 8; };
    if (!in_bounds(white_.first) || !in_bounds(white_.second) ||
        !in_bounds(black_.first) || !in_bounds(black_.second)) {
        throw std::domain_error("Queen position out of bounds");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::position chess_board::white() const { return white_; }

chess_board::position chess_board::black() const { return black_; }

chess_board::operator std::string() const {
    std::ostringstream oss;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (c > 0) {
                oss << ' ';
            }
            if (white_.first == r && white_.second == c) {
                oss << 'W';
            } else if (black_.first == r && black_.second == c) {
                oss << 'B';
            } else {
                oss << '_';
            }
        }
        if (r < 7) {
            oss << '\n';
        }
    }
    return oss.str();
}

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) {
        return true;
    }
    // Same column
    if (white_.second == black_.second) {
        return true;
    }
    // Same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

}  // namespace queen_attack
