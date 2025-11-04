#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <map>
#include <string>

namespace queen_attack {

chess_board::chess_board(const std::string& white, const std::string& black) {
    // Create mappings without using character arithmetic
    static const std::map<char, std::int8_t> file_map = {
        {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3},
        {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}
    };
    
    static const std::map<char, std::int8_t> rank_map = {
        {'1', 0}, {'2', 1}, {'3', 2}, {'4', 3},
        {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}
    };
    
    // Parse white position
    if (white.size() != 2) {
        throw std::domain_error("Invalid white queen position");
    }
    char white_file_char = white[0];
    char white_rank_char = white[1];
    
    // Check if characters are valid using the maps
    if (((file_map.find(white_file_char) == file_map.end()) || 
         (rank_map.find(white_rank_char) == rank_map.end()))) {
        throw std::domain_error("Invalid white queen position");
    }
    white_.first = file_map.at(white_file_char);
    white_.second = rank_map.at(white_rank_char);
    
    // Parse black position
    if (black.size() != 2) {
        throw std::domain_error("Invalid black queen position");
    }
    char black_file_char = black[0];
    char black_rank_char = black[1];
    
    if (((file_map.find(black_file_char) == file_map.end()) || 
         (rank_map.find(black_rank_char) == rank_map.end()))) {
        throw std::domain_error("Invalid black queen position");
    }
    black_.first = file_map.at(black_file_char);
    black_.second = rank_map.at(black_rank_char);
    
    // Check if queens are on the same square
    if (((white_.first == black_.first) && (white_.second == black_.second))) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (((white_.first == black_.first) || (white_.second == black_.second))) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Cast to int to avoid issues with std::abs and int8_t
    if ((std::abs((static_cast<int>(white_.first) - static_cast<int>(black_.first))) == 
         std::abs((static_cast<int>(white_.second) - static_cast<int>(black_.second))))) {
        return true;
    }
    return false;
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_.first), static_cast<int>(white_.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_.first), static_cast<int>(black_.second));
}

}  // namespace queen_attack
