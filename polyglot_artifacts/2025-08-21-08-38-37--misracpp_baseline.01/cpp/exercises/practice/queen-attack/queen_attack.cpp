#include "queen_attack.h"
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {}

std::pair<int, int> chess_board::white() const noexcept {
    return white_;
}

std::pair<int, int> chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    // Same row
    if (white_.first == black_.first)
        return true;
    // Same column
    if (white_.second == black_.second)
        return true;
    // Same diagonal
    if (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second))
        return true;
    return false;
}

}  // namespace queen_attack
