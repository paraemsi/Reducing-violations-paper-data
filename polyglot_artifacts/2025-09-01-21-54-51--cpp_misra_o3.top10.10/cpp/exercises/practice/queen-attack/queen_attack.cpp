#include "queen_attack.h"

#include <sstream>

namespace queen_attack {

namespace {

/*  Check that an index lies within the 8 × 8 board.  */
[[nodiscard]] bool is_within_board(const board_index idx) noexcept
{
    return (idx < chess_board::board_size);
}

}   // unnamed namespace

chess_board::chess_board(const std::pair<board_index, board_index> white_pos,
                         const std::pair<board_index, board_index> black_pos)
    : m_white{white_pos},
      m_black{black_pos}
{
    /*  Validate input positions.  */
    if((m_white == m_black) ||
       !is_within_board(m_white.first)  || !is_within_board(m_white.second) ||
       !is_within_board(m_black.first) || !is_within_board(m_black.second))
    {
        throw std::domain_error("invalid queen position");
    }
}

std::pair<std::int32_t, std::int32_t> chess_board::white() const noexcept
{
    return { static_cast<std::int32_t>(m_white.first),
             static_cast<std::int32_t>(m_white.second) };
}

std::pair<std::int32_t, std::int32_t> chess_board::black() const noexcept
{
    return { static_cast<std::int32_t>(m_black.first),
             static_cast<std::int32_t>(m_black.second) };
}

bool chess_board::can_attack() const noexcept
{
    /*  Row and column deltas expressed as signed values to allow negatives.  */
    const std::int16_t row_delta =
        static_cast<std::int16_t>(m_white.second) -
        static_cast<std::int16_t>(m_black.second);

    const std::int16_t col_delta =
        static_cast<std::int16_t>(m_white.first) -
        static_cast<std::int16_t>(m_black.first);

    /*  Same row or same column implies an attack is possible.  */
    if((row_delta == 0) || (col_delta == 0))
    {
        return true;
    }

    /*  Diagonal attack: absolute row and column differences are equal.  */
    const std::int16_t row_diff = (row_delta < 0) ? -row_delta : row_delta;
    const std::int16_t col_diff = (col_delta < 0) ? -col_delta : col_delta;

    return (row_diff == col_diff);
}

chess_board::operator std::string() const
{
    std::ostringstream board_builder;

    for(board_index row{0U}; row < board_size; ++row)
    {
        for(board_index col{0U}; col < board_size; ++col)
        {
            char piece{'_'};

            if((row == m_white.second) && (col == m_white.first))
            {
                piece = 'W';
            }
            else if((row == m_black.second) && (col == m_black.first))
            {
                piece = 'B';
            }

            board_builder << piece;

            if(col < (board_size - static_cast<board_index>(1U)))
            {
                board_builder << ' ';
            }
        }

        if(row < (board_size - static_cast<board_index>(1U)))
        {
            board_builder << '\n';
        }
    }

    return board_builder.str();
}

}   // namespace queen_attack
