#include "queen_attack.h"
#include <cstdint>
#include <stdexcept>

namespace queen_attack {

bool can_attack(const position& white, const position& black) noexcept
{
    const std::uint16_t w_row = static_cast<std::uint16_t>(white.row);
    const std::uint16_t b_row = static_cast<std::uint16_t>(black.row);
    const std::uint16_t w_col = static_cast<std::uint16_t>(white.column);
    const std::uint16_t b_col = static_cast<std::uint16_t>(black.column);

    const std::uint16_t d_row = (w_row > b_row) ? (w_row - b_row) : (b_row - w_row);
    const std::uint16_t d_col = (w_col > b_col) ? (w_col - b_col) : (b_col - w_col);

    const bool same_row = (white.row == black.row);
    const bool same_col = (white.column == black.column);
    const bool diag = (d_row == d_col);

    return ((same_row) || (same_col) || (diag));
}

chess_board::chess_board(board_coordinate white, board_coordinate black)
    : white_(white), black_(black)
{
    const bool white_row_valid = ((white_.first >= 0) && (white_.first < 8));
    const bool white_col_valid = ((white_.second >= 0) && (white_.second < 8));
    const bool black_row_valid = ((black_.first >= 0) && (black_.first < 8));
    const bool black_col_valid = ((black_.second >= 0) && (black_.second < 8));

    if ((!white_row_valid) || (!white_col_valid) || (!black_row_valid) || (!black_col_valid)) {
        throw std::domain_error("queen position out of bounds");
    }

    const bool same_pos = ((white_.first == black_.first) && (white_.second == black_.second));
    if (same_pos) {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

board_coordinate chess_board::white() const noexcept
{
    return white_;
}

board_coordinate chess_board::black() const noexcept
{
    return black_;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row = (white_.first == black_.first);
    const bool same_col = (white_.second == black_.second);

    const std::int32_t d_row = ((white_.first > black_.first) ? (white_.first - black_.first) : (black_.first - white_.first));
    const std::int32_t d_col = ((white_.second > black_.second) ? (white_.second - black_.second) : (black_.second - white_.second));
    const bool diag = (d_row == d_col);

    return ((same_row) || (same_col) || (diag));
}

}  // namespace queen_attack
