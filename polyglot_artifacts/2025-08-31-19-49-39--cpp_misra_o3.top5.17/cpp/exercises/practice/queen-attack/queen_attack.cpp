#include "queen_attack.h"

#include <stdexcept>
#include <sstream>

namespace queen_attack {

namespace {
constexpr std::uint8_t board_size{static_cast<std::uint8_t>(8U)};

bool is_valid_position(const coordinate& pos) noexcept
{
    return (pos.first < board_size) && (pos.second < board_size);
}
}  // namespace

chess_board::chess_board(coordinate white_pos, coordinate black_pos)
    : white_pos_{white_pos}, black_pos_{black_pos}
{
    if (white_pos_ == black_pos_)
    {
        throw std::domain_error("Queens cannot occupy the same square.");
    }
    if ((!is_valid_position(white_pos_)) || (!is_valid_position(black_pos_)))
    {
        throw std::domain_error("Position out of board bounds.");
    }
}

coordinate chess_board::white() const noexcept
{
    return white_pos_;
}

coordinate chess_board::black() const noexcept
{
    return black_pos_;
}

bool chess_board::can_attack() const noexcept
{
    const std::uint8_t row_white{white_pos_.second};
    const std::uint8_t col_white{white_pos_.first};
    const std::uint8_t row_black{black_pos_.second};
    const std::uint8_t col_black{black_pos_.first};

    const bool same_row{row_white == row_black};
    const bool same_col{col_white == col_black};

    const std::int16_t row_diff{
        static_cast<std::int16_t>(row_white) - static_cast<std::int16_t>(row_black)};
    const std::int16_t col_diff{
        static_cast<std::int16_t>(col_white) - static_cast<std::int16_t>(col_black)};

    const bool same_diag{(row_diff == col_diff) || (row_diff == -col_diff)};

    return (same_row || same_col) || same_diag;
}

chess_board::operator std::string() const
{
    std::ostringstream oss{};

    for (std::uint8_t row{static_cast<std::uint8_t>(0U)}; row < board_size; ++row)
    {
        for (std::uint8_t col{static_cast<std::uint8_t>(0U)}; col < board_size; ++col)
        {
            if (col != static_cast<std::uint8_t>(0U))
            {
                oss << ' ';
            }

            if ((white_pos_.first == col) && (white_pos_.second == row))
            {
                oss << 'W';
            }
            else if ((black_pos_.first == col) && (black_pos_.second == row))
            {
                oss << 'B';
            }
            else
            {
                oss << 'O';
            }
        }

        if (row != static_cast<std::uint8_t>(board_size - static_cast<std::uint8_t>(1U)))
        {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace queen_attack
