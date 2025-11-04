#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black}
{
    if (!is_valid(white_) || !is_valid(black_)) {
        throw std::domain_error("Queen position must be on a standard 8x8 chessboard.");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same position.");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_;
}

std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    int row1 = white_.first, col1 = white_.second;
    int row2 = black_.first, col2 = black_.second;
    return (row1 == row2) ||
           (col1 == col2) ||
           (std::abs(row1 - row2) == std::abs(col1 - col2));
}

bool chess_board::is_valid(const std::pair<int, int>& pos) {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}

} // namespace queen_attack
