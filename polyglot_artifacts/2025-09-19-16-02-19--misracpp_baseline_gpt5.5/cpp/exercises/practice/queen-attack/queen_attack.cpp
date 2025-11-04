#include "queen_attack.h"

#include <stdexcept>
#include <string>
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {
    auto valid = [](const std::pair<int, int>& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    };
    if (!valid(white_) || !valid(black_)) {
        throw std::domain_error("position out of bounds");
    }
    if (white_ == black_) {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const noexcept { return white_; }
std::pair<int, int> chess_board::black() const noexcept { return black_; }

bool chess_board::can_attack() const noexcept {
    // same row
    if (white_.first == black_.first) return true;
    // same column
    if (white_.second == black_.second) return true;
    // same diagonal
    return std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::string s;
    s.reserve(8 * (8 * 2)); // approximate reserve
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (r == white_.first && c == white_.second) {
                s += 'W';
            } else if (r == black_.first && c == black_.second) {
                s += 'B';
            } else {
                s += '_';
            }
            if (c != 7) s += ' ';
        }
        if (r != 7) s += '\n';
    }
    return s;
}

}  // namespace queen_attack
