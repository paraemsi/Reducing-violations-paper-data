#include "queen_attack.h"

namespace queen_attack {

queen::queen(int row, int col) : row_{row}, col_{col} {}

std::pair<int, int> queen::position() const {
    return {row_, col_};
}

#include <cstdlib>
#include <stdexcept>

bool can_attack(const queen& q1, const queen& q2) noexcept {
    auto [r1, c1] = q1.position();
    auto [r2, c2] = q2.position();

    // Same row
    if (r1 == r2) return true;
    // Same column
    if (c1 == c2) return true;
    // Same diagonal
    if (std::abs(r1 - r2) == std::abs(c1 - c2)) return true;

    return false;
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos_{white}, black_pos_{black}
{
    // Check for out-of-bounds
    auto in_bounds = [](std::pair<int, int> pos) {
        return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
    };
    if (!in_bounds(white) || !in_bounds(black)) {
        throw std::domain_error("Queen position out of bounds");
    }
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const noexcept {
    return white_pos_;
}

std::pair<int, int> chess_board::black() const noexcept {
    return black_pos_;
}

bool chess_board::can_attack() const noexcept {
    // Use the same logic as can_attack(queen, queen)
    int r1 = white_pos_.first, c1 = white_pos_.second;
    int r2 = black_pos_.first, c2 = black_pos_.second;
    if (r1 == r2) return true;
    if (c1 == c2) return true;
    if (std::abs(r1 - r2) == std::abs(c1 - c2)) return true;
    return false;
}

}  // namespace queen_attack
