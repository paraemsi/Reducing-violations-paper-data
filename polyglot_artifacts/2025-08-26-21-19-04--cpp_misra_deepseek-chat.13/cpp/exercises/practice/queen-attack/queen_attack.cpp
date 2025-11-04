#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(const std::string& white, const std::string& black) {
    // Parse white position
    if (white.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char white_col = std::tolower(white[0]);
    char white_row = white[1];
    if (((white_col < 'a') || (white_col > 'h')) || ((white_row < '1') || (white_row > '8'))) {
        throw std::domain_error("Invalid position");
    }
    white_pos.first = static_cast<std::int8_t>((white_col - 'a'));
    white_pos.second = static_cast<std::int8_t>((white_row - '1'));
    
    // Parse black position
    if (black.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char black_col = std::tolower(black[0]);
    char black_row = black[1];
    if (((black_col < 'a') || (black_col > 'h')) || ((black_row < '1') || (black_row > '8'))) {
        throw std::domain_error("Invalid position");
    }
    black_pos.first = static_cast<std::int8_t>((black_col - 'a'));
    black_pos.second = static_cast<std::int8_t>((black_row - '1'));
    
    if (((white_pos.first == black_pos.first)) && ((white_pos.second == black_pos.second))) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (((white_pos.first == black_pos.first)) || ((white_pos.second == black_pos.second))) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Cast to int to avoid issues with std::abs and std::int8_t
    int row_diff = (static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first));
    int col_diff = (static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second));
    if ((std::abs(row_diff)) == (std::abs(col_diff))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
