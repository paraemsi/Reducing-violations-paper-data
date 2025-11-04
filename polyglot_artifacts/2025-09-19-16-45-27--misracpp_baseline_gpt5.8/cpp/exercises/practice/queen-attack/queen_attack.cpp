#include "queen_attack.h"

#include <stdexcept>
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    auto on_board = [](const position& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    };
    if (!on_board(white_) || !on_board(black_)) {
        throw std::domain_error{"Queen position must be on the board"};
    }
    if (white_ == black_) {
        throw std::domain_error{"Queens cannot share the same position"};
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
    board.reserve((8 * 8) + (7 * 8)); // 64 cells + 7 spaces per row

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            char cell = '_';
            if (white_.first == r && white_.second == c) {
                cell = 'W';
            } else if (black_.first == r && black_.second == c) {
                cell = 'B';
            }
            board.push_back(cell);
            if (c < 7) {
                board.push_back(' ');
            }
        }
        if (r < 7) {
            board.push_back('\n');
        }
    }

    return board;
}

bool chess_board::can_attack() const {
    // Same row or same column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }

    // Diagonal: absolute row difference equals absolute column difference
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

}  // namespace queen_attack
