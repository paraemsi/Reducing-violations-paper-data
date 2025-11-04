#include "queen_attack.h"
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
{
    const std::int32_t w_r = static_cast<std::int32_t>(white.first);
    const std::int32_t w_c = static_cast<std::int32_t>(white.second);
    const std::int32_t b_r = static_cast<std::int32_t>(black.first);
    const std::int32_t b_c = static_cast<std::int32_t>(black.second);

    const bool w_row_invalid = ((w_r < 0) || (w_r >= 8));
    const bool w_col_invalid = ((w_c < 0) || (w_c >= 8));
    const bool b_row_invalid = ((b_r < 0) || (b_r >= 8));
    const bool b_col_invalid = ((b_c < 0) || (b_c >= 8));

    if ((w_row_invalid || w_col_invalid) || (b_row_invalid || b_col_invalid))
    {
        throw std::domain_error("queen position out of bounds");
    }

    const bool same_square = ((w_r == b_r) && (w_c == b_c));
    if (same_square)
    {
        throw std::domain_error("queens cannot occupy the same square");
    }

    w_row_ = static_cast<std::int32_t>(w_r);
    w_col_ = static_cast<std::int32_t>(w_c);
    b_row_ = static_cast<std::int32_t>(b_r);
    b_col_ = static_cast<std::int32_t>(b_c);
}

auto chess_board::white() const noexcept -> std::pair<int, int>
{
    return std::pair<int, int>{static_cast<int>(w_row_), static_cast<int>(w_col_)};
}

auto chess_board::black() const noexcept -> std::pair<int, int>
{
    return std::pair<int, int>{static_cast<int>(b_row_), static_cast<int>(b_col_)};
}

auto chess_board::can_attack() const noexcept -> bool
{
    const bool same_row = (w_row_ == b_row_);
    const bool same_col = (w_col_ == b_col_);

    const std::int32_t dr_raw = (w_row_ - b_row_);
    const std::int32_t dc_raw = (w_col_ - b_col_);
    const std::int32_t dr = ((dr_raw < 0) ? (-dr_raw) : dr_raw);
    const std::int32_t dc = ((dc_raw < 0) ? (-dc_raw) : dc_raw);

    const bool same_diag = (dr == dc);

    return ((same_row || same_col) || same_diag);
}

auto can_attack(const position& white, const position& black) noexcept -> bool
{
    const std::int32_t wr = white.row;
    const std::int32_t wc = white.column;
    const std::int32_t br = black.row;
    const std::int32_t bc = black.column;

    const bool same_row = (wr == br);
    const bool same_col = (wc == bc);

    const std::int32_t dr_raw = (wr - br);
    const std::int32_t dc_raw = (wc - bc);
    const std::int32_t dr = ((dr_raw < 0) ? (-dr_raw) : dr_raw);
    const std::int32_t dc = ((dc_raw < 0) ? (-dc_raw) : dc_raw);

    const bool same_diag = (dr == dc);

    return ((same_row || same_col) || same_diag);
}

}  // namespace queen_attack
