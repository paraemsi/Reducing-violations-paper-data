#include "queen_attack.h"

#include <cstdlib>   // std::abs
#include <sstream>
#include <string>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    auto in_bounds = [](const position& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    };

    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("queen position out of bounds");
    }

    if (white_ == black_) {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

position chess_board::white() const {
    return white_;
}

position chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    return white_.first == black_.first
        || white_.second == black_.second
        || std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::ostringstream os;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            char ch = '_';
            if (white_.first == r && white_.second == c) {
                ch = 'W';
            } else if (black_.first == r && black_.second == c) {
                ch = 'B';
            }
            os << ch;
            if (c != 7) {
                os << ' ';
            }
        }
        os << '\n';
    }
    return os.str();
}

}  // namespace queen_attack
