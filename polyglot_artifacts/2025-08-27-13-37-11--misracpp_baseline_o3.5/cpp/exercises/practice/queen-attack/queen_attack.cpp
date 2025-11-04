#include "queen_attack.h"

#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <sstream>

namespace queen_attack {

namespace {
bool is_valid(const std::pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}
}  // namespace

chess_board::chess_board(std::pair<int,int> white_position,
                         std::pair<int,int> black_position)
    : white_pos_(white_position),
      black_pos_(black_position) {

    if (!is_valid(white_position) || !is_valid(black_position)) {
        throw std::domain_error("Queens must be placed on the board");
    }
    if (white_position == black_position) {
        throw std::domain_error("Queens cannot share the same space");
    }
}

std::pair<int,int> chess_board::white() const {
    return white_pos_;
}

std::pair<int,int> chess_board::black() const {
    return black_pos_;
}

bool chess_board::can_attack() const {
    // Same row
    if (white_pos_.first == black_pos_.first) {
        return true;
    }
    // Same column
    if (white_pos_.second == black_pos_.second) {
        return true;
    }
    // Same diagonal
    return std::abs(white_pos_.first - black_pos_.first) ==
           std::abs(white_pos_.second - black_pos_.second);
}

chess_board::operator std::string() const {
    std::ostringstream board;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char mark = '_';
            if (white_pos_.first == row && white_pos_.second == col) {
                mark = 'W';
            } else if (black_pos_.first == row && black_pos_.second == col) {
                mark = 'B';
            }
            board << mark;
            if (col < 7) {
                board << ' ';
            }
        }
        if (row < 7) {
            board << '\n';
        }
    }
    return board.str();
}

}  // namespace queen_attack
