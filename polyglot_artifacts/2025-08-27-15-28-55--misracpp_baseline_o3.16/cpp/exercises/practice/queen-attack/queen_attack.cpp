#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cmath>

namespace queen_attack {

constexpr int board_size = 8;

namespace {
bool is_valid_position(const std::pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < board_size &&
           pos.second >= 0 && pos.second < board_size;
}
}  // namespace

chess_board::chess_board() noexcept
    : white_{0, 3}, black_{7, 3} {}

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_{white}, black_{black} {
    if (!is_valid_position(white_) || !is_valid_position(black_)) {
        throw std::domain_error("Queen position must be on the board");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int,int> chess_board::white() const noexcept {
    return white_;
}

std::pair<int,int> chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    if (white_.first == black_.first) return true;          // same row
    if (white_.second == black_.second) return true;        // same column
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);         // diagonal
}

chess_board::operator std::string() const noexcept {
    std::ostringstream oss;
    for (int row = 0; row < board_size; ++row) {
        for (int col = 0; col < board_size; ++col) {
            char cell = '_';
            if (white_ == std::make_pair(row, col)) {
                cell = 'W';
            } else if (black_ == std::make_pair(row, col)) {
                cell = 'B';
            }
            oss << cell;
            if (col < board_size - 1) {
                oss << ' ';
            }
        }
        if (row < board_size - 1) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace queen_attack
