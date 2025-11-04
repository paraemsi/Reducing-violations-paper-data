#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_(white), black_(black) {
    // Check if positions are valid
    if (white.first < 0 || white.first >= 8 || white.second < 0 || white.second >= 8 ||
        black.first < 0 || black.first >= 8 || black.second < 0 || black.second >= 8) {
        throw std::domain_error("Queen position must be on the board");
    }
    // Check if queens are on the same square
    if (white == black) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_;
}

std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
