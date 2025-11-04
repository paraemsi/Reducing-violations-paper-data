#include "queen_attack.h"
#include <cmath>

namespace queen_attack {

#include <stdexcept>

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {
    // Check white position
    if (white.first < 0 || white.second < 0)
        throw std::domain_error("Queen position must have non-negative row and column");
    if (white.first > 7 || white.second > 7)
        throw std::domain_error("Queen position must be on the board");

    // Check black position
    if (black.first < 0 || black.second < 0)
        throw std::domain_error("Queen position must have non-negative row and column");
    if (black.first > 7 || black.second > 7)
        throw std::domain_error("Queen position must be on the board");

    // Check distinctness
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
