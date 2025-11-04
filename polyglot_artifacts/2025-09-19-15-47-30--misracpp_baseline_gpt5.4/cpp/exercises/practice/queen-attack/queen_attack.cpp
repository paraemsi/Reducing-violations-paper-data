#include "queen_attack.h"

#include <cstdlib> // std::abs
#include <string>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    auto in_bounds = [](int v) { return v >= 0 && v < 8; };
    if (!in_bounds(white_.first) || !in_bounds(white_.second) ||
        !in_bounds(black_.first) || !in_bounds(black_.second)) {
        throw std::domain_error("Queen position must be on the board");
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

chess_board::operator std::string() const {
    std::string board;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (col > 0) {
                board += ' ';
            }
            if (white_ == std::make_pair(row, col)) {
                board += 'W';
            } else if (black_ == std::make_pair(row, col)) {
                board += 'B';
            } else {
                board += '_';
            }
        }
        if (row < 7) {
            board += '\n';
        }
    }
    return board;
}

bool chess_board::can_attack() const {
    int dr = std::abs(white_.first - black_.first);
    int dc = std::abs(white_.second - black_.second);
    return dr == 0 || dc == 0 || dr == dc;
}

}  // namespace queen_attack
