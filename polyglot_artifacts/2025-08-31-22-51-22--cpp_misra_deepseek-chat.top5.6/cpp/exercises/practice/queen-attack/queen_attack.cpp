#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<coordinate_t, coordinate_t> white, std::pair<coordinate_t, coordinate_t> black) 
    : white_(white), black_(black) {
    if ((white_.first >= 8) || 
        (white_.second >= 8) ||
        (black_.first >= 8) || 
        (black_.second >= 8)) {
        throw std::domain_error("Invalid position");
    }
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::chess_board(const std::pair<std::string, std::string>& positions) {
    // Parse white position
    if (positions.first.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char white_file = std::tolower(static_cast<unsigned char>(positions.first[0]));
    char white_rank = positions.first[1];
    
    if ((white_file < 'a') || (white_file > 'h') || (white_rank < '1') || (white_rank > '8')) {
        throw std::domain_error("Invalid position");
    }
    white_.first = static_cast<coordinate_t>(white_file - 'a');
    white_.second = static_cast<coordinate_t>('8' - white_rank); // Convert to 0-based row index
    
    // Parse black position
    if (positions.second.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char black_file = std::tolower(static_cast<unsigned char>(positions.second[0]));
    char black_rank = positions.second[1];
    
    if ((black_file < 'a') || (black_file > 'h') || (black_rank < '1') || (black_rank > '8')) {
        throw std::domain_error("Invalid position");
    }
    black_.first = static_cast<coordinate_t>(black_file - 'a');
    black_.second = static_cast<coordinate_t>('8' - black_rank); // Convert to 0-based row index
    
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return {static_cast<int>(white_.first), static_cast<int>(white_.second)};
}

std::pair<int, int> chess_board::black() const {
    return {static_cast<int>(black_.first), static_cast<int>(black_.second)};
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_.first == black_.first) || (white_.second == black_.second)) {
        return true;
    }
    // Check if on the same diagonal
    if (std::abs(static_cast<int>(white_.first - black_.first)) == std::abs(static_cast<int>(white_.second - black_.second))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
