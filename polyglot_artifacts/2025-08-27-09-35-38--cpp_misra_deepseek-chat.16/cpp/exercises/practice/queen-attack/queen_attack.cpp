#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) {
    // Check if positions are valid (0-7 for both coordinates)
    if ((white.first < 0) || (white.first > 7) || 
        (white.second < 0) || (white.second > 7) ||
        (black.first < 0) || (black.first > 7) || 
        (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Invalid position");
    }
    // Check if queens are on the same square
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Convert to coord_t
    white_pos.first = static_cast<coord_t>(white.first);
    white_pos.second = static_cast<coord_t>(white.second);
    black_pos.first = static_cast<coord_t>(black.first);
    black_pos.second = static_cast<coord_t>(black.second);
}

std::pair<int, int> chess_board::white() const {
    // Convert from coord_t to int to match the test expectations
    return std::make_pair(static_cast<int>(white_pos.first), static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    // Convert from coord_t to int to match the test expectations
    return std::make_pair(static_cast<int>(black_pos.first), static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Cast to int to avoid issues with std::abs and coord_t
    int file_diff = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    int rank_diff = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    if (std::abs(file_diff) == std::abs(rank_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
