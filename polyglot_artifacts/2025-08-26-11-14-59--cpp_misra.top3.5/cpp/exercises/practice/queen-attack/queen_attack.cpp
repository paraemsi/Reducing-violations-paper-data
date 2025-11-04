#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_pos(white), black_pos(black)
{
    // Validate positions are on the board
    if ((white.first < 0) || (white.first > 7) ||
        (white.second < 0) || (white.second > 7) ||
        (black.first < 0) || (black.first > 7) ||
        (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Queen position out of bounds");
    }
    // Validate not same position
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const
{
    return white_pos;
}

std::pair<int, int> chess_board::black() const
{
    return black_pos;
}

bool chess_board::can_attack() const
{
    // Row and column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Diagonal
    if (((white_pos.first > black_pos.first) ? (white_pos.first - black_pos.first) : (black_pos.first - white_pos.first)) ==
        ((white_pos.second > black_pos.second) ? (white_pos.second - black_pos.second) : (black_pos.second - white_pos.second))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
