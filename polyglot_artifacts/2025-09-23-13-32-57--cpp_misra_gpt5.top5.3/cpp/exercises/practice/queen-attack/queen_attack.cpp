#include "queen_attack.h"
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(position white, position black) noexcept
    : white_{white},
      black_{black} {
}

position chess_board::white() const noexcept {
    return white_;
}

position chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    const bool same_row = (white_.row == black_.row);
    const bool same_col = (white_.column == black_.column);

    const std::int32_t w_row = white_.row;
    const std::int32_t b_row = black_.row;
    const std::int32_t w_col = white_.column;
    const std::int32_t b_col = black_.column;

    const std::int32_t row_diff = (w_row > b_row)
        ? (w_row - b_row)
        : (b_row - w_row);

    const std::int32_t col_diff = (w_col > b_col)
        ? (w_col - b_col)
        : (b_col - w_col);

    const bool same_diag = (row_diff == col_diff);

    return ((same_row || same_col) || same_diag);
}

}  // namespace queen_attack
