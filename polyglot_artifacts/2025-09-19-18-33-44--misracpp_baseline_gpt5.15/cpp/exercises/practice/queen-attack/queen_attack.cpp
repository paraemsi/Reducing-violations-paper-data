#include "queen_attack.h"

#include <cmath>
#include <sstream>
#include <stdexcept>

namespace queen_attack {

static bool in_bounds(const position& p) {
    return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
}

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("Positions must be within 0..7 for both row and column");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position chess_board::white() const {
    return white_;
}

position chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // same row or same column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    // diagonal
    int dr = std::abs(white_.first - black_.first);
    int dc = std::abs(white_.second - black_.second);
    return dr == dc;
}

chess_board::operator std::string() const {
    std::ostringstream out;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (c > 0) out << ' ';
            if (r == white_.first && c == white_.second) {
                out << 'W';
            } else if (r == black_.first && c == black_.second) {
                out << 'B';
            } else {
                out << '_';
            }
        }
        if (r < 7) out << '\n';
    }
    return out.str();
}

}  // namespace queen_attack
