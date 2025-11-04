#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <sstream>

namespace queen_attack {

namespace {

// Validate that the position lies on an 8 × 8 board.
bool is_valid_position(const std::pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}

} // namespace

chess_board::chess_board() : chess_board({0,3}, {7,3}) {}

chess_board::chess_board(std::pair<int,int> white_pos, std::pair<int,int> black_pos)
    : white_{white_pos}, black_{black_pos} {

    if (!is_valid_position(white_pos) || !is_valid_position(black_pos) || white_pos == black_pos) {
        throw std::domain_error("Invalid queen position");
    }
}

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) {
        return true;
    }
    // Same column
    if (white_.second == black_.second) {
        return true;
    }
    // Same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::ostringstream board;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char cell = '_';
            if (white_ == std::make_pair(row, col)) {
                cell = 'W';
            } else if (black_ == std::make_pair(row, col)) {
                cell = 'B';
            }
            board << cell;
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
