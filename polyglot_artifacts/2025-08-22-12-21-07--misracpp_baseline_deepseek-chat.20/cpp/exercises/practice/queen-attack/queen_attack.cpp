#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_(white), black_(black) {
    // Validate positions are within the board
    if (white_.first < 0 || white_.first > 7 || white_.second < 0 || white_.second > 7 ||
        black_.first < 0 || black_.first > 7 || black_.second < 0 || black_.second > 7) {
        throw std::domain_error("Invalid position");
    }
    if (white_ == black_) {
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

chess_board::operator std::string() const {
    std::stringstream board;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == white_.first && j == white_.second) {
                board << "W";
            } else if (i == black_.first && j == black_.second) {
                board << "B";
            } else {
                board << "_";
            }
            if (j < 7) {
                board << " ";
            }
        }
        board << "\n";
    }
    return board.str();
}

}  // namespace queen_attack
