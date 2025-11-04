#include "queen_attack.h"

#include <cmath>
#include <stdexcept>
#include <sstream>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    auto in_bounds = [](const position& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    };
    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("Queen position must be on board");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot share the same position");
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

chess_board::operator std::string() const {
    std::ostringstream os;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            char ch = 'O';
            if (white_ == position{r, c}) ch = 'W';
            if (black_ == position{r, c}) ch = 'B';
            os << ch;
            if (c < 7) os << ' ';
        }
        os << '\n';
    }
    return os.str();
}

}  // namespace queen_attack
