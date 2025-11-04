#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_(std::make_pair(static_cast<std::int32_t>(white.first), static_cast<std::int32_t>(white.second))), 
      black_(std::make_pair(static_cast<std::int32_t>(black.first), static_cast<std::int32_t>(black.second))) {
    if (white_ == black_) {
        throw std::domain_error("Queens cannot be on the same square");
    }
    // Check if positions are valid (0-7)
    if ((white_.first < 0) || (white_.first > 7) || (white_.second < 0) || (white_.second > 7) ||
        (black_.first < 0) || (black_.first > 7) || (black_.second < 0) || (black_.second > 7)) {
        throw std::domain_error("Invalid queen position");
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
    if ((white_.first == black_.first) || (white_.second == black_.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second)) {
        return true;
    }
    return false;
}

chess_board::operator std::string() const {
    std::string board;
    for (std::int32_t i = 0; i < 8; i++) {
        for (std::int32_t j = 0; j < 8; j++) {
            if ((j == white_.first) && (i == white_.second)) {
                board += 'W';
            } else if ((j == black_.first) && (i == black_.second)) {
                board += 'B';
            } else {
                board += '_';
            }
            if (j < 7) {
                board += ' ';
            }
        }
        if (i < 7) {
            board += '\n';
        }
    }
    return board;
}

}  // namespace queen_attack
