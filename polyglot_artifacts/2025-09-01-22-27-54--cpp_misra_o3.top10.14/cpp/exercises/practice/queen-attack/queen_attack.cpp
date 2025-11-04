#include "queen_attack.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>

namespace queen_attack {

namespace
{
constexpr std::size_t board_dimension{8U};

constexpr bool is_valid_coordinate(const coordinate_t value)
{
    return (value >= static_cast<coordinate_t>(0)) &&
           (static_cast<std::size_t>(value) < board_dimension);
}

[[nodiscard]] std::uint8_t to_uint8(const coordinate_t value)
{
    /* value is validated to be within [0, 7] before conversion */
    return static_cast<std::uint8_t>(value);
}
} // namespace

chess_board::chess_board(const position& white_pos, const position& black_pos)
{
    if ((!is_valid_coordinate(white_pos.first)) || (!is_valid_coordinate(white_pos.second)) ||
        (!is_valid_coordinate(black_pos.first)) || (!is_valid_coordinate(black_pos.second)))
    {
        throw std::domain_error("Queen position must be on the board");
    }

    if ((white_pos.first == black_pos.first) && (white_pos.second == black_pos.second))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }

    m_white_row  = to_uint8(white_pos.first);
    m_white_col  = to_uint8(white_pos.second);
    m_black_row  = to_uint8(black_pos.first);
    m_black_col  = to_uint8(black_pos.second);
}

std::string chess_board::board() const
{
    std::array<std::array<char, board_dimension>, board_dimension> squares{};

    for (auto& row : squares)
    {
        row.fill('.');
    }

    squares[m_white_row][m_white_col] = 'W';
    squares[m_black_row][m_black_col] = 'B';

    std::ostringstream out_stream{};

    for (std::size_t row{0U}; row < board_dimension; ++row)
    {
        for (std::size_t col{0U}; col < board_dimension; ++col)
        {
            out_stream << squares[row][col];
            if (col < (board_dimension - 1U))
            {
                out_stream << ' ';
            }
        }
        if (row < (board_dimension - 1U))
        {
            out_stream << '\n';
        }
    }

    return out_stream.str();
}

bool chess_board::can_attack() const
{
    const std::uint8_t row_diff = static_cast<std::uint8_t>(
        (m_white_row > m_black_row) ? (m_white_row - m_black_row)
                                    : (m_black_row - m_white_row));
    const std::uint8_t col_diff = static_cast<std::uint8_t>(
        (m_white_col > m_black_col) ? (m_white_col - m_black_col)
                                    : (m_black_col - m_white_col));

    return (row_diff == static_cast<std::uint8_t>(0)) || (col_diff == static_cast<std::uint8_t>(0)) ||
           (row_diff == col_diff);
}

chess_board::position chess_board::white() const
{
    return {static_cast<coordinate_t>(m_white_row), static_cast<coordinate_t>(m_white_col)};
}

chess_board::position chess_board::black() const
{
    return {static_cast<coordinate_t>(m_black_row), static_cast<coordinate_t>(m_black_col)};
}

}  // namespace queen_attack
