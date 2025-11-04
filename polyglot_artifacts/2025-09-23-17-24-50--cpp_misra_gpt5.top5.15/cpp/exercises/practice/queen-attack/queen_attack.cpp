#include "queen_attack.h"
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(coordinate white, coordinate black)
{
    const std::int32_t wr = static_cast<std::int32_t>(white.first);
    const std::int32_t wc = static_cast<std::int32_t>(white.second);
    const std::int32_t br = static_cast<std::int32_t>(black.first);
    const std::int32_t bc = static_cast<std::int32_t>(black.second);

    const bool wr_ok = ((wr >= 0) && (wr < 8));
    const bool wc_ok = ((wc >= 0) && (wc < 8));
    const bool br_ok = ((br >= 0) && (br < 8));
    const bool bc_ok = ((bc >= 0) && (bc < 8));

    if ((!wr_ok) || (!wc_ok) || (!br_ok) || (!bc_ok)) {
        throw std::domain_error("queen positions must be on the board");
    }

    const bool same_square = ((wr == br) && (wc == bc));
    if (same_square) {
        throw std::domain_error("queens cannot share the same position");
    }

    w_row_ = wr;
    w_col_ = wc;
    b_row_ = br;
    b_col_ = bc;
}

auto chess_board::white() const -> coordinate
{
    return coordinate{static_cast<int>(w_row_), static_cast<int>(w_col_)};
}

auto chess_board::black() const -> coordinate
{
    return coordinate{static_cast<int>(b_row_), static_cast<int>(b_col_)};
}

auto chess_board::can_attack() const -> bool
{
    const bool same_row = (w_row_ == b_row_);
    const bool same_column = (w_col_ == b_col_);

    const std::int32_t row_diff = (w_row_ > b_row_) ? (w_row_ - b_row_) : (b_row_ - w_row_);
    const std::int32_t col_diff = (w_col_ > b_col_) ? (w_col_ - b_col_) : (b_col_ - w_col_);

    const bool same_diagonal = (row_diff == col_diff);

    return (same_row || same_column || same_diagonal);
}

bool can_attack(const position& white, const position& black)
{
    const std::uint32_t wr = static_cast<std::uint32_t>(white.row);
    const std::uint32_t br = static_cast<std::uint32_t>(black.row);
    const std::uint32_t wc = static_cast<std::uint32_t>(white.column);
    const std::uint32_t bc = static_cast<std::uint32_t>(black.column);

    const bool same_row = (white.row == black.row);
    const bool same_column = (white.column == black.column);

    const std::uint32_t row_diff = (wr > br) ? (wr - br) : (br - wr);
    const std::uint32_t col_diff = (wc > bc) ? (wc - bc) : (bc - wc);

    const bool same_diagonal = (row_diff == col_diff);

    return (same_row || same_column || same_diagonal);
}

}  // namespace queen_attack
