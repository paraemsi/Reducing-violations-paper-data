#include "queen_attack.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <cctype>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board() 
    : white_pos(std::make_pair(static_cast<std::int8_t>(0), static_cast<std::int8_t>(3))), 
      black_pos(std::make_pair(static_cast<std::int8_t>(7), static_cast<std::int8_t>(3))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos(std::make_pair(static_cast<std::int8_t>(white.first), 
                               static_cast<std::int8_t>(white.second))),
      black_pos(std::make_pair(static_cast<std::int8_t>(black.first), 
                               static_cast<std::int8_t>(black.second))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
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
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal by comparing absolute differences
    // Cast to int to ensure proper signed arithmetic
    const int dx = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    const int dy = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    // Check if the absolute differences are equal
    if (dx == dy) {
        return true;
    }
    if (dx == -dy) {
        return true;
    }
    return false;
}

chess_board::operator std::string() const {
    std::stringstream board;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Compare using the internal int8_t types
            if ((static_cast<std::int8_t>(i) == white_pos.first) && 
                (static_cast<std::int8_t>(j) == white_pos.second)) {
                board << 'W';
            } else if ((static_cast<std::int8_t>(i) == black_pos.first) && 
                       (static_cast<std::int8_t>(j) == black_pos.second)) {
                board << 'B';
            } else {
                board << '_';
            }
            if (j < 7) {
                board << ' ';
            }
        }
        board << '\n';
    }
    return board.str();
}

}  // namespace queen_attack
