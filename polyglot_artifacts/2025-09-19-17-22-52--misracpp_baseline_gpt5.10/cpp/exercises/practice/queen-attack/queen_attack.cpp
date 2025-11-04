#include "queen_attack.h"

#include <stdexcept>
#include <cstdlib>

namespace queen_attack {

namespace {
    constexpr int board_min = 0;
    constexpr int board_max = 7;

    bool in_bounds(const position& p) {
        return p.first >= board_min && p.first <= board_max &&
               p.second >= board_min && p.second <= board_max;
    }
}

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    if (!in_bounds(white_) || !in_bounds(black_) || (white_ == black_)) {
        throw std::domain_error("invalid queen position");
    }
}

position chess_board::white() const noexcept {
    return white_;
}

position chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    if (white_.first == black_.first) return true;   // same row
    if (white_.second == black_.second) return true; // same column
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

}  // namespace queen_attack
