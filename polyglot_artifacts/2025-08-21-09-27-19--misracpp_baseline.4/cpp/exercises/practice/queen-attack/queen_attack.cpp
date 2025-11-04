#include "queen_attack.h"
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos(white), black_pos(black) {}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Same row
    if (white_pos.first == black_pos.first)
        return true;
    // Same column
    if (white_pos.second == black_pos.second)
        return true;
    // Same diagonal
    if (std::abs(white_pos.first - black_pos.first) == std::abs(white_pos.second - black_pos.second))
        return true;
    return false;
}

}  // namespace queen_attack
