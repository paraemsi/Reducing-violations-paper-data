#include "queen_attack.h"
#include <stdexcept>
#include <cstdlib> // for std::abs

namespace queen_attack {

chess_board::chess_board(position white_pos, position black_pos)
    : white_{white_pos}, black_{black_pos} {
    auto in_bounds = [](const position& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    };
    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("position out of bounds");
    }
    if (white_ == black_) {
        throw std::domain_error("queens cannot occupy the same square");
    }
}

position chess_board::white() const { return white_; }
position chess_board::black() const { return black_; }

bool chess_board::can_attack() const {
    const int dr = white_.first - black_.first;
    const int dc = white_.second - black_.second;
    return dr == 0 || dc == 0 || std::abs(dr) == std::abs(dc);
}

}  // namespace queen_attack
