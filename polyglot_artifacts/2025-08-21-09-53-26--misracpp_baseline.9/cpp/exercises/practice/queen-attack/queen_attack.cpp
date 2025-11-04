#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{std::move(white)}, black_{std::move(black)} 
{
    // Check if positions are on the board (0 <= row/col <= 7)
    if (white_.first < 0 || white_.first > 7)
        throw std::domain_error("White queen row out of bounds");
    if (white_.second < 0 || white_.second > 7)
        throw std::domain_error("White queen column out of bounds");
    if (black_.first < 0 || black_.first > 7)
        throw std::domain_error("Black queen row out of bounds");
    if (black_.second < 0 || black_.second > 7)
        throw std::domain_error("Black queen column out of bounds");
    // Check if positions are distinct
    if (white_ == black_)
        throw std::domain_error("Queens cannot occupy the same position");
}

std::pair<int, int> chess_board::white() const {
    return white_;
}

std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) return true;
    // Same column
    if (white_.second == black_.second) return true;
    // Same diagonal
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second)) return true;
    return false;
}

} // namespace queen_attack
