#include "queen_attack.h"

#include <string>
#include <cstdlib>   // for std::abs

namespace queen_attack {

namespace {
    bool in_bounds(const std::pair<int,int>& pos) {
        return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
    }
}

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_pos_{white}, black_pos_{black} {

    if (!in_bounds(white) || !in_bounds(black) || white == black) {
        throw std::domain_error("invalid queen position");
    }
}

std::pair<int,int> chess_board::white() const noexcept {
    return white_pos_;
}

std::pair<int,int> chess_board::black() const noexcept {
    return black_pos_;
}

bool chess_board::can_attack() const noexcept {
    const int row_diff = white_pos_.first - black_pos_.first;
    const int col_diff = white_pos_.second - black_pos_.second;

    // Same row or same column
    if (row_diff == 0 || col_diff == 0) {
        return true;
    }
    // Same diagonal
    return std::abs(row_diff) == std::abs(col_diff);
}

chess_board::operator std::string() const {
    std::string board;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (row == white_pos_.first && col == white_pos_.second) {
                board += 'W';
            } else if (row == black_pos_.first && col == black_pos_.second) {
                board += 'B';
            } else {
                board += '_';
            }
            if (col < 7) {
                board += ' ';
            }
        }
        board += '\n';
    }
    return board;
}

}  // namespace queen_attack
