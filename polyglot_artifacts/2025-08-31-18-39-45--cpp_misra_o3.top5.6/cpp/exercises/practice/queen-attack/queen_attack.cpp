#include "queen_attack.h"

#include <sstream>
#include <stdexcept>

namespace queen_attack {

namespace {
/* Size of one board edge. */
constexpr coord_t board_size { static_cast<coord_t>(8U) };

/* Validate that a coordinate lies within the board. */
[[nodiscard]] bool is_valid_coordinate(coord_t coord) noexcept
{
    return (coord < board_size);
}
} // namespace

chess_board::chess_board(std::pair<int, int> white_pos, std::pair<int, int> black_pos)
{
    if ((white_pos.first < 0) ||
        (white_pos.first >= static_cast<int>(board_size)) ||
        (white_pos.second < 0) ||
        (white_pos.second >= static_cast<int>(board_size)) ||
        (black_pos.first < 0) ||
        (black_pos.first >= static_cast<int>(board_size)) ||
        (black_pos.second < 0) ||
        (black_pos.second >= static_cast<int>(board_size)))
    {
        throw std::domain_error("Queen position out of bounds");
    }

    if ((white_pos.first == black_pos.first) &&
        (white_pos.second == black_pos.second))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }

    /* All validations passed – store positions in the board representation. */
    m_white = { { static_cast<coord_t>(white_pos.first), static_cast<coord_t>(white_pos.second) } };
    m_black = { { static_cast<coord_t>(black_pos.first), static_cast<coord_t>(black_pos.second) } };
}

std::pair<int, int> chess_board::white() const noexcept
{
    return { static_cast<int>(m_white[0U]), static_cast<int>(m_white[1U]) };
}

std::pair<int, int> chess_board::black() const noexcept
{
    return { static_cast<int>(m_black[0U]), static_cast<int>(m_black[1U]) };
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row { m_white[0U] == m_black[0U] };
    const bool same_col { m_white[1U] == m_black[1U] };

    const std::int16_t row_diff {
        static_cast<std::int16_t>(m_white[0U]) -
        static_cast<std::int16_t>(m_black[0U])
    };
    const std::int16_t col_diff {
        static_cast<std::int16_t>(m_white[1U]) -
        static_cast<std::int16_t>(m_black[1U])
    };

    const bool same_diag { (row_diff == col_diff) || (row_diff == -col_diff) };

    return (same_row || same_col || same_diag);
}

chess_board::operator std::string() const
{
    std::ostringstream os;

    for (coord_t row { 0U }; row < board_size; ++row)
    {
        for (coord_t col { 0U }; col < board_size; ++col)
        {
            char cell { '_' };

            if ((row == m_white[0U]) && (col == m_white[1U]))
            {
                cell = 'W';
            }
            else if ((row == m_black[0U]) && (col == m_black[1U]))
            {
                cell = 'B';
            }

            os << cell;

            if (col < (board_size - static_cast<coord_t>(1)))
            {
                os << ' ';
            }
        }

        if (row < (board_size - static_cast<coord_t>(1)))
        {
            os << '\n';
        }
    }

    return os.str();
}

}  // namespace queen_attack
