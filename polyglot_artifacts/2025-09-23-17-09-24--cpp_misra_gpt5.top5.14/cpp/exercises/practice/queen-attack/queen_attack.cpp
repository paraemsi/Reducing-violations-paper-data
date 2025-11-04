#include "queen_attack.h"
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{0, 0},
      black_{0, 0} {
    if ((white == black)) {
        throw std::domain_error("queens cannot occupy the same position");
    }

    const std::int32_t lower = 0;
    const std::int32_t upper = 8;

    const bool white_in_bounds = (((white.first >= lower) && (white.first < upper)) && ((white.second >= lower) && (white.second < upper)));
    const bool black_in_bounds = (((black.first >= lower) && (black.first < upper)) && ((black.second >= lower) && (black.second < upper)));

    if ((!white_in_bounds) || (!black_in_bounds)) {
        throw std::domain_error("queen position out of bounds");
    }

    white_.first = white.first;
    white_.second = white.second;
    black_.first = black.first;
    black_.second = black.second;
}

position chess_board::white() const noexcept {
    return std::pair<int, int>{static_cast<int>(white_.first), static_cast<int>(white_.second)};
}

position chess_board::black() const noexcept {
    return std::pair<int, int>{static_cast<int>(black_.first), static_cast<int>(black_.second)};
}

bool chess_board::can_attack() const noexcept {
    const bool same_row = (white_.first == black_.first);
    const bool same_col = (white_.second == black_.second);
    const std::int32_t dr = (white_.first - black_.first);
    const std::int32_t dc = (white_.second - black_.second);
    const bool same_diag = (((dr == dc) || (dr == (-dc))));

    return ((same_row || same_col) || same_diag);
}

}  // namespace queen_attack
