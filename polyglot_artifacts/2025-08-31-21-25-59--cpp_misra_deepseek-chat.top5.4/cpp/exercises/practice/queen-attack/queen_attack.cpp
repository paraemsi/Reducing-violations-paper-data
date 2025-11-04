#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black) 
    : white_(std::make_pair(static_cast<coord_t>(white.first), static_cast<coord_t>(white.second))),
      black_(std::make_pair(static_cast<coord_t>(black.first), static_cast<coord_t>(black.second))) {
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_.first), static_cast<int>(white_.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_.first), static_cast<int>(black_.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (((white_.first == black_.first)) || ((white_.second == black_.second))) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Use static_cast to ensure we're dealing with the right types for abs
    int row_diff = std::abs(static_cast<int>(white_.first) - static_cast<int>(black_.first));
    int col_diff = std::abs(static_cast<int>(white_.second) - static_cast<int>(black_.second));
    if ((row_diff == col_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
