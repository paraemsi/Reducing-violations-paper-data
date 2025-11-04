#include "queen_attack.h"
#include <string>
#include <stdexcept>
#include <utility>
#include <cmath>
#include <cstdlib>

namespace queen_attack {

namespace {
    std::pair<int, int> parse_position(const std::string& pos) {
        if (pos.size() != 2) {
            throw std::domain_error("Invalid position format");
        }
        // Parse column
        char file = pos[0];
        if (file < 'a' || file > 'h') {
            throw std::domain_error("Invalid file");
        }
        int column = file - 'a';
        
        // Parse row
        char rank = pos[1];
        if (rank < '1' || rank > '8') {
            throw std::domain_error("Invalid rank");
        }
        // Convert '1' to '8' to 7 down to 0
        int row = '8' - rank;
        
        return std::make_pair(column, row);
    }
}

chess_board::chess_board(const std::string& white, const std::string& black) {
    white_ = parse_position(white);
    black_ = parse_position(black);
    
    // Check if queens are on the same square
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
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
    if ((white_.first == black_.first) || (white_.second == black_.second)) {
        return true;
    }
    // Check if on the same diagonal
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
