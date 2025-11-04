#include "queen_attack.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int,int> white,
                         std::pair<int,int> black)
    : white_pos_{white}, black_pos_{black}
{
    auto in_range = [](int c){ return c >= 0 && c < 8; };

    if (!in_range(white.first) || !in_range(white.second) ||
        !in_range(black.first) || !in_range(black.second)) {
        throw std::domain_error{"Queen must be placed on the board"};
    }
    if (white == black) {
        throw std::domain_error{"Queens cannot share the same position"};
    }
}

std::pair<int,int> chess_board::white() const noexcept {
    return white_pos_;
}

std::pair<int,int> chess_board::black() const noexcept {
    return black_pos_;
}

bool chess_board::can_attack() const noexcept {
    // Same row
    if (white_pos_.first == black_pos_.first) return true;
    // Same column
    if (white_pos_.second == black_pos_.second) return true;
    // Same diagonal
    return std::abs(white_pos_.first - black_pos_.first) ==
           std::abs(white_pos_.second - black_pos_.second);
}

chess_board::operator std::string() const {
    std::ostringstream board;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (row == white_pos_.first && col == white_pos_.second) {
                board << 'W';
            } else if (row == black_pos_.first && col == black_pos_.second) {
                board << 'B';
            } else {
                board << '_';
            }
            if (col < 7) board << ' ';
        }
        if (row < 7) board << '\n';
    }
    return board.str();
}

std::ostream& operator<<(std::ostream& os,
                         const chess_board& board) {
    return os << static_cast<std::string>(board);
}

}  // namespace queen_attack
