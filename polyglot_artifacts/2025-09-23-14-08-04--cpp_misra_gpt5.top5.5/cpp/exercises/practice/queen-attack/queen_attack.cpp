#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board() noexcept
    : white_{position{std::int32_t{0}, std::int32_t{3}}},
      black_{position{std::int32_t{7}, std::int32_t{3}}}
{
}

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black}
{
    if ((!in_bounds(white_.row)) || (!in_bounds(white_.column)) || (!in_bounds(black_.row)) || (!in_bounds(black_.column))) {
        throw std::domain_error("Position out of bounds");
    }

    if ((white_.row == black_.row) && (white_.column == black_.column)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position chess_board::white() const noexcept
{
    return white_;
}

position chess_board::black() const noexcept
{
    return black_;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row = (white_.row == black_.row);
    const bool same_col = (white_.column == black_.column);

    const std::int32_t dr_raw = (white_.row - black_.row);
    const std::int32_t dc_raw = (white_.column - black_.column);

    const std::int32_t abs_dr = ((dr_raw < 0) ? (-dr_raw) : dr_raw);
    const std::int32_t abs_dc = ((dc_raw < 0) ? (-dc_raw) : dc_raw);

    const bool same_diag = (abs_dr == abs_dc);

    return (((same_row || same_col) || same_diag));
}

}  // namespace queen_attack
