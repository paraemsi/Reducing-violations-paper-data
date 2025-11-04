#include "queen_attack.h"

#include <sstream>

namespace queen_attack {

namespace {

/* helper to compute absolute value for a signed 16-bit integer */
constexpr std::int16_t abs_val(std::int16_t value) noexcept
{
    return (value < 0) ? static_cast<std::int16_t>(-value) : value;
}

} // unnamed namespace

/* ---------- chess_board -------------------------------------------------- */

chess_board::chess_board() noexcept
    : white_pos_{ position{ static_cast<coordinate_t>(0U), static_cast<coordinate_t>(3U) } },
      black_pos_{ position{ static_cast<coordinate_t>(7U), static_cast<coordinate_t>(3U) } }
{
    /* default ctor establishes a legal starting configuration */
}

chess_board::chess_board(position white_pos, position black_pos)
    : white_pos_{ white_pos }, black_pos_{ black_pos }
{
    if ((white_pos.row == black_pos.row) && (white_pos.col == black_pos.col))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }

    if ((!is_valid_position(white_pos)) || (!is_valid_position(black_pos)))
    {
        throw std::domain_error("Position is not on the board");
    }
}

bool chess_board::can_attack() const noexcept
{
    const std::int16_t row_diff =
        static_cast<std::int16_t>(white_pos_.row) - static_cast<std::int16_t>(black_pos_.row);
    const std::int16_t col_diff =
        static_cast<std::int16_t>(white_pos_.col) - static_cast<std::int16_t>(black_pos_.col);

    /* same row or same column */
    if ((row_diff == 0) || (col_diff == 0))
    {
        return true;
    }

    /* diagonals: |Δrow| == |Δcol| */
    return abs_val(row_diff) == abs_val(col_diff);
}

position chess_board::white() const noexcept
{
    return white_pos_;
}

position chess_board::black() const noexcept
{
    return black_pos_;
}

constexpr bool chess_board::is_valid_position(position pos) noexcept
{
    return (pos.row < board_size) && (pos.col < board_size);
}

chess_board::operator std::string() const
{
    std::ostringstream oss;

    for (coordinate_t row { 0U }; row < board_size; ++row)
    {
        for (coordinate_t col { 0U }; col < board_size; ++col)
        {
            if ((row == white_pos_.row) && (col == white_pos_.col))
            {
                oss << 'W';
            }
            else if ((row == black_pos_.row) && (col == black_pos_.col))
            {
                oss << 'B';
            }
            else
            {
                oss << '_';
            }

            if (col < (board_size - static_cast<coordinate_t>(1U)))
            {
                oss << ' ';
            }
        }

        if (row < (board_size - static_cast<coordinate_t>(1U)))
        {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace queen_attack
