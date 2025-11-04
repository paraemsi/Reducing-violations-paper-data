#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

namespace {
bool in_bounds(const position& p) {
    return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
}
} // namespace

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("position out of bounds");
    }
    if (white_ == black_) {
        throw std::domain_error("queens cannot share the same position");
    }
}

position chess_board::white() const {
    return white_;
}

position chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) return true;
    // Same column
    if (white_.second == black_.second) return true;
    // Same diagonal
    return std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

}  // namespace queen_attack
