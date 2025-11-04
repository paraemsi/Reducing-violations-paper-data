#include "queen_attack.h"

#include <cmath>
#include <stdexcept>
#include <string>

namespace queen_attack {

namespace {
bool is_valid(const position& p) {
    return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
}
}  // namespace

chess_board::chess_board(position white, position black)
    : white_(white), black_(black) {
    if (!is_valid(white_) || !is_valid(black_)) {
        throw std::domain_error("Position out of bounds");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

position chess_board::white() const { return white_; }

position chess_board::black() const { return black_; }

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) return true;
    // Same column
    if (white_.second == black_.second) return true;
    // Same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::string out;
    out.reserve(8 * 15 + 7);  // Each row: 15 chars ("x x x x x x x x"), 7 newlines
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            char ch = '_';
            if (white_.first == r && white_.second == c) {
                ch = 'W';
            } else if (black_.first == r && black_.second == c) {
                ch = 'B';
            }
            out.push_back(ch);
            if (c < 7) out.push_back(' ');
        }
        if (r < 7) out.push_back('\n');
    }
    return out;
}

}  // namespace queen_attack
