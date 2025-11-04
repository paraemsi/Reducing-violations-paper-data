#include "queen_attack.h"

#include <sstream>

namespace queen_attack {

void chess_board::validate_position(std::pair<coord_t, coord_t> position)
{
    if ((position.first >= BOARD_SIZE) || (position.second >= BOARD_SIZE))
    {
        throw std::domain_error("Queen position must be on the board");
    }
}

chess_board::chess_board(std::pair<coord_t, coord_t> white,
                         std::pair<coord_t, coord_t> black) :
    m_white_row{white.first},
    m_white_col{white.second},
    m_black_row{black.first},
    m_black_col{black.second}
{
    validate_position(white);
    validate_position(black);

    if ((white.first == black.first) && (white.second == black.second))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<chess_board::coord_t, chess_board::coord_t> chess_board::white() const
{
    return std::pair<coord_t, coord_t>{m_white_row, m_white_col};
}

std::pair<chess_board::coord_t, chess_board::coord_t> chess_board::black() const
{
    return std::pair<coord_t, coord_t>{m_black_row, m_black_col};
}

bool chess_board::can_attack() const
{
    if (m_white_row == m_black_row)
    {
        return true;
    }

    if (m_white_col == m_black_col)
    {
        return true;
    }

    const std::int32_t row_delta {(m_white_row > m_black_row)
                                      ? (m_white_row - m_black_row)
                                      : (m_black_row - m_white_row)};

    const std::int32_t col_delta {(m_white_col > m_black_col)
                                      ? (m_white_col - m_black_col)
                                      : (m_black_col - m_white_col)};

    return row_delta == col_delta;
}

chess_board::operator std::string() const
{
    std::ostringstream board_stream {};

    for (coord_t row {0}; row < BOARD_SIZE; ++row)
    {
        for (coord_t col {0}; col < BOARD_SIZE; ++col)
        {
            char square {'.'};

            if ((row == m_white_row) && (col == m_white_col))
            {
                square = 'W';
            }
            else if ((row == m_black_row) && (col == m_black_col))
            {
                square = 'B';
            }

            board_stream << square;

            if (col < (BOARD_SIZE - 1))
            {
                board_stream << ' ';
            }
        }

        if (row < (BOARD_SIZE - 1))
        {
            board_stream << '\n';
        }
    }

    return board_stream.str();
}

}  // namespace queen_attack
