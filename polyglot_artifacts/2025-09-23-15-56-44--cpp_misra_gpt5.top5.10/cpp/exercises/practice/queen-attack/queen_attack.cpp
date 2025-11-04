#include "queen_attack.h"

#include <stdexcept>

namespace queen_attack {

namespace {
    constexpr std::int32_t board_min = 0;
    constexpr std::int32_t board_max = 7;

    constexpr std::int32_t i32_abs(std::int32_t v) noexcept {
        return (v >= 0) ? v : (-v);
    }

    constexpr bool in_bounds(coordinate r, coordinate c) noexcept {
        return ((r >= board_min) && (r <= board_max) && (c >= board_min) && (c <= board_max));
    }
}

chess_board::chess_board(position white, position black)
    : white_{white}
    , black_{black}
{
    if (!in_bounds(white_.first, white_.second)) {
        throw std::domain_error("white position out of bounds");
    } else {
        // no-op
    }

    if (!in_bounds(black_.first, black_.second)) {
        throw std::domain_error("black position out of bounds");
    } else {
        // no-op
    }

    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("queens cannot occupy the same position");
    } else {
        // no-op
    }
}

position chess_board::white() const noexcept {
    return white_;
}

position chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    const bool same_row = (white_.first == black_.first);
    const bool same_col = (white_.second == black_.second);
    const bool same_diag = (i32_abs(white_.first - black_.first) == i32_abs(white_.second - black_.second));
    return ((same_row || same_col) || same_diag);
}

chess_board::operator std::string() const {
    std::string board;

    for (coordinate r = coordinate{0}; r <= board_max; ++r) {
        for (coordinate c = coordinate{0}; c <= board_max; ++c) {
            char cell = '_';
            if ((white_.first == r) && (white_.second == c)) {
                cell = 'W';
            } else {
                if ((black_.first == r) && (black_.second == c)) {
                    cell = 'B';
                } else {
                    // no-op
                }
            }
            board.push_back(cell);
            if (c < board_max) {
                board.push_back(' ');
            } else {
                // no-op
            }
        }
        if (r < board_max) {
            board.push_back('\n');
        } else {
            // no-op
        }
    }

    return board;
}

}  // namespace queen_attack
