#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <string>
#include <utility>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_(white), black_(black) {
    // Validate positions are on the board
    if (white_.first < 0 || white_.first > 7 || white_.second < 0 || white_.second > 7) {
        throw std::domain_error("Queen position must be on the board");
    }
    if (black_.first < 0 || black_.first > 7 || black_.second < 0 || black_.second > 7) {
        throw std::domain_error("Queen position must be on the board");
    }
    // Check if queens are on the same square
    if (white_.first == black_.first && white_.second == black_.second) {
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
    // Check if they're on the same row or column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    // Check if they're on the same diagonal
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
