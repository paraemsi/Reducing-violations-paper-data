#include "queen_attack.h"

#include <sstream>
#include <stdexcept>
#include <cstdlib>   // std::abs

namespace queen_attack {

namespace {

// Ensure the position lies within the 8 × 8 board.
void validate_position(const std::pair<int, int>& pos) {
    if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7) {
        throw std::domain_error{"Queen position must be within 0..7 for both coordinates"};
    }
}

}  // namespace

// Constructors
chess_board::chess_board(std::pair<int, int> white_pos, std::pair<int, int> black_pos)
    : white_pos_{white_pos}, black_pos_{black_pos} {
    validate_position(white_pos_);
    validate_position(black_pos_);
    if (white_pos_ == black_pos_) {
        throw std::domain_error{"Queens cannot occupy the same square"};
    }
}

// Accessors
std::pair<int, int> chess_board::white() const noexcept {
    return white_pos_;
}

std::pair<int, int> chess_board::black() const noexcept {
    return black_pos_;
}

// Core logic
bool chess_board::can_attack() const noexcept {
    return (white_pos_.first == black_pos_.first) ||                     // same row
           (white_pos_.second == black_pos_.second) ||                   // same column
           (std::abs(white_pos_.first - black_pos_.first) ==             // same diagonal
            std::abs(white_pos_.second - black_pos_.second));
}

// String conversion
chess_board::operator std::string() const {
    std::ostringstream os;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (row == white_pos_.first && col == white_pos_.second) {
                os << 'W';
            } else if (row == black_pos_.first && col == black_pos_.second) {
                os << 'B';
            } else {
                os << '_';
            }
            if (col != 7) {
                os << ' ';
            }
        }
        os << '\n';
    }
    return os.str();
}

}  // namespace queen_attack
