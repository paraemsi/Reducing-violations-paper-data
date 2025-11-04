#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>

using namespace std;

namespace queen_attack {

chess_board::chess_board(pair<int, int> white, pair<int, int> black) 
    : white_(white), black_(black) {
    if (white_ == black_) {
        throw domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7)
    if (white_.first < 0 || white_.first > 7 || white_.second < 0 || white_.second > 7 ||
        black_.first < 0 || black_.first > 7 || black_.second < 0 || black_.second > 7) {
        throw domain_error("Invalid position");
    }
}

chess_board::chess_board(const pair<string, string>& positions) {
    // Parse white position
    string white_pos = positions.first;
    if (white_pos.size() != 2) throw domain_error("Invalid position");
    int white_col = white_pos[0] - 'a';
    int white_row = 7 - (white_pos[1] - '1'); // Adjust for chess board orientation (1 at the bottom is row 7)
    
    // Check if valid
    if (white_col < 0 || white_col > 7 || white_row < 0 || white_row > 7) {
        throw domain_error("Invalid position");
    }
    
    // Parse black position
    string black_pos = positions.second;
    if (black_pos.size() != 2) throw domain_error("Invalid position");
    int black_col = black_pos[0] - 'a';
    int black_row = 7 - (black_pos[1] - '1'); // Adjust for chess board orientation
    
    // Check if valid
    if (black_col < 0 || black_col > 7 || black_row < 0 || black_row > 7) {
        throw domain_error("Invalid position");
    }
    
    // Store as (column, row) to match the problem's description
    white_ = make_pair(white_col, white_row);
    black_ = make_pair(black_col, black_row);
    
    if (white_ == black_) {
        throw domain_error("Queens cannot occupy the same position");
    }
}

pair<int, int> chess_board::white() const {
    return white_;
}

pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // Check if on the same row, column, or diagonal
    // Now white_ and black_ are (column, row)
    if (white_.first == black_.first) return true;           // Same column
    if (white_.second == black_.second) return true;         // Same row
    if (abs(white_.first - black_.first) == abs(white_.second - black_.second)) return true; // Same diagonal
    return false;
}

}  // namespace queen_attack
