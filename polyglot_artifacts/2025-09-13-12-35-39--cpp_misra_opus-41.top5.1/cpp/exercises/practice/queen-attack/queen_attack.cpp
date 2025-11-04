#include "queen_attack.h"
#include <cstdlib>
#include <cmath>

namespace queen_attack {

queen::queen(std::int32_t row, std::int32_t column) 
    : row_(row), column_(column) {
    // Validate position is within chess board bounds (0-7)
    if ((row < 0) || (row > 7) || (column < 0) || (column > 7)) {
        throw std::domain_error("Queen position must be on the board");
    }
}

queen::queen(std::pair<std::int32_t, std::int32_t> position)
    : row_(position.first), column_(position.second) {
    // Validate position is within chess board bounds (0-7)
    if ((row_ < 0) || (row_ > 7) || (column_ < 0) || (column_ > 7)) {
        throw std::domain_error("Queen position must be on the board");
    }
}

std::pair<std::int32_t, std::int32_t> queen::position() const {
    return std::make_pair(row_, column_);
}

bool queen::operator==(const queen& other) const {
    return ((row_ == other.row_) && (column_ == other.column_));
}

chess_board::chess_board(const queen& white_queen, const queen& black_queen)
    : white_queen_(white_queen), black_queen_(black_queen) {
    // Check if queens are on the same position
    if (white_queen == black_queen) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

const queen& chess_board::white() const {
    return white_queen_;
}

const queen& chess_board::black() const {
    return black_queen_;
}

bool chess_board::can_attack() const {
    // Check if on same row
    if (white_queen_.row_ == black_queen_.row_) {
        return true;
    }
    
    // Check if on same column
    if (white_queen_.column_ == black_queen_.column_) {
        return true;
    }
    
    // Check if on same diagonal
    // Two queens are on the same diagonal if the absolute difference
    // between their rows equals the absolute difference between their columns
    std::int32_t row_diff = std::abs(white_queen_.row_ - black_queen_.row_);
    std::int32_t col_diff = std::abs(white_queen_.column_ - black_queen_.column_);
    
    if (row_diff == col_diff) {
        return true;
    }
    
    return false;
}

}  // namespace queen_attack
