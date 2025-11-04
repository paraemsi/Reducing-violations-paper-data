#include "queen_attack.h"
#include <cmath>

namespace queen_attack {

#include <stdexcept>

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {
    // Check that both positions are on the board (0 <= row < 8, 0 <= col < 8)
    if (white.first < 0 || white.first > 7)
        throw std::domain_error("White queen row out of bounds");
    if (white.second < 0 || white.second > 7)
        throw std::domain_error("White queen column out of bounds");
    if (black.first < 0 || black.first > 7)
        throw std::domain_error("Black queen row out of bounds");
    if (black.second < 0 || black.second > 7)
        throw std::domain_error("Black queen column out of bounds");
    // Check that the positions are not the same
    if (white == black)
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
    if (white_.first == black_.first)
        return true;
    // Same column
    if (white_.second == black_.second)
        return true;
    // Same diagonal
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second))
        return true;
    return false;
}

}  // namespace queen_attack
