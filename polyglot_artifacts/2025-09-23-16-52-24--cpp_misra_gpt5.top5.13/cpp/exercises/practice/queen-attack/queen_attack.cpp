#include "queen_attack.h"

#include <stdexcept>
#include <cstdint>

namespace queen_attack {

bool chess_board::is_valid_coord(std::int32_t v) noexcept {
    const std::int32_t limit = static_cast<std::int32_t>(8);
    return ((v >= static_cast<std::int32_t>(0)) && (v < limit));
}

chess_board::chess_board() noexcept
    : white_{static_cast<std::int32_t>(0), static_cast<std::int32_t>(3)}
    , black_{static_cast<std::int32_t>(7), static_cast<std::int32_t>(3)} {
}

chess_board::chess_board(const position_t& white, const position_t& black)
    : white_{white}
    , black_{black} {
    const bool in_range = ((is_valid_coord(white_.first) && is_valid_coord(white_.second)) && (is_valid_coord(black_.first) && is_valid_coord(black_.second)));
    if (!in_range) {
        throw std::domain_error("Queen position must be on the board");
    }
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position_t chess_board::white() const noexcept {
    return white_;
}

position_t chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    const std::int32_t wx = white_.first;
    const std::int32_t wy = white_.second;
    const std::int32_t bx = black_.first;
    const std::int32_t by = black_.second;

    const bool same_row = (wy == by);
    const bool same_col = (wx == bx);

    const std::int32_t dx = ((wx > bx) ? (wx - bx) : (bx - wx));
    const std::int32_t dy = ((wy > by) ? (wy - by) : (by - wy));

    const bool same_diag = (dx == dy);

    return ((same_row || same_col) || same_diag);
}

}  // namespace queen_attack
