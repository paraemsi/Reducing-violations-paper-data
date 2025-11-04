#include "queen_attack.h"

#include <stdexcept>
#include <sstream>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_(white), black_(black) {
    auto in_bounds = [](const position& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    };
    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("Queen positions must be on the board");
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
    // Same row
    if (white_.first == black_.first) return true;
    // Same column
    if (white_.second == black_.second) return true;
    // Same diagonal
    int dr = white_.first - black_.first;
    if (dr < 0) dr = -dr;
    int dc = white_.second - black_.second;
    if (dc < 0) dc = -dc;
    return dr == dc;
}

chess_board::operator std::string() const {
    std::ostringstream oss;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char c = '_';
            if (white_.first == row && white_.second == col) {
                c = 'W';
            } else if (black_.first == row && black_.second == col) {
                c = 'B';
            }
            oss << c;
            if (col < 7) {
                oss << ' ';
            }
        }
        if (row < 7) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace queen_attack
