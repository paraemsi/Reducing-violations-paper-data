#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cctype>

namespace queen_attack {

chess_board::chess_board(position_t white, position_t black) 
    : white_pos(white), black_pos(black) {
    if ((white_pos.first >= 8) || 
        (white_pos.second >= 8) ||
        (black_pos.first >= 8) || 
        (black_pos.second >= 8)) {
        throw std::domain_error("Positions must be on the board");
    }
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be on the same square");
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
    white_pos.first = static_cast<coordinate_t>(white_file - 'a');
    white_pos.second = static_cast<coordinate_t>('8' - white_rank); // Convert to 0-based row index
    
    // Parse black position
    if (positions.second.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char black_file = std::tolower(static_cast<unsigned char>(positions.second[0]));
    char black_rank = positions.second[1];
    
    if ((black_file < 'a') || (black_file > 'h') || (black_rank < '1') || (black_rank > '8')) {
        throw std::domain_error("Invalid position");
    }
    black_pos.first = static_cast<coordinate_t>(black_file - 'a');
    black_pos.second = static_cast<coordinate_t>('8' - black_rank); // Convert to 0-based row index
    
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), 
                          static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), 
                          static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (((white_pos.first == black_pos.first)) || ((white_pos.second == black_pos.second))) {
        return true;
    }
    // Check if on the same diagonal by comparing the squares of differences
    coordinate_t dx = static_cast<coordinate_t>((white_pos.first - black_pos.first));
    coordinate_t dy = static_cast<coordinate_t>((white_pos.second - black_pos.second));
    // Compare the squares to check if |dx| == |dy|
    if (((dx * dx) == (dy * dy))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
