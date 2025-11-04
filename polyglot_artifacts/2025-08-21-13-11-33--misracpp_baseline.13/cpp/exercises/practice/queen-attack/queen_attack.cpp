#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_(white), black_(black)
{
    // Check white position
    if (white.first < 0 || white.first > 7)
        throw std::domain_error("White queen row out of bounds");
    if (white.second < 0 || white.second > 7)
        throw std::domain_error("White queen column out of bounds");

    // Check black position
    if (black.first < 0 || black.first > 7)
        throw std::domain_error("Black queen row out of bounds");
    if (black.second < 0 || black.second > 7)
        throw std::domain_error("Black queen column out of bounds");

    // Check distinctness
    if (white == black)
        throw std::domain_error("Queens cannot occupy the same position");
}

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) return true;
    // Same column
    if (white_.second == black_.second) return true;
    // Same diagonal
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second)) return true;
    return false;
}

}  // namespace queen_attack
