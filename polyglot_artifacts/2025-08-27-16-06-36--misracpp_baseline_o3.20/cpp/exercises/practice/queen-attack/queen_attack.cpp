#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cmath>

namespace queen_attack {

bool chess_board::in_bounds(const square_t& pos) noexcept {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}

chess_board::chess_board(square_t white, square_t black)
    : white_{white}, black_{black} {

    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error{"Queen position must be on the board"};
    }
    if (white_ == black_) {
        throw std::domain_error{"Queens cannot share the same square"};
    }
}

bool chess_board::can_attack() const noexcept {
    // same row
    if (white_.first == black_.first) return true;
    // same column
    if (white_.second == black_.second) return true;
    // same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

std::string chess_board::board() const {
    std::ostringstream oss;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (r == white_.first && c == white_.second) {
                oss << 'W';
            } else if (r == black_.first && c == black_.second) {
                oss << 'B';
            } else {
                oss << '_';
            }
            if (c < 7) {
                oss << ' ';
            }
        }
        if (r < 7) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace queen_attack
