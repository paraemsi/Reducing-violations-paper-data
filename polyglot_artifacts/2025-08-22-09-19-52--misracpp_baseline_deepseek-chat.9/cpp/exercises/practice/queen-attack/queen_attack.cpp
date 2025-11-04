#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <string>
#include <cctype>
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(white), black_pos(black) {
    // Check if positions are valid (0-7 for both coordinates)
    if (white_pos.first < 0 || white_pos.first > 7 || 
        white_pos.second < 0 || white_pos.second > 7 ||
        black_pos.first < 0 || black_pos.first > 7 || 
        black_pos.second < 0 || black_pos.second > 7) {
        throw std::domain_error("Invalid queen position");
    }
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (white_pos.first == black_pos.first || white_pos.second == black_pos.second) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    int dx = std::abs(white_pos.first - black_pos.first);
    int dy = std::abs(white_pos.second - black_pos.second);
    if (dx == dy) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
