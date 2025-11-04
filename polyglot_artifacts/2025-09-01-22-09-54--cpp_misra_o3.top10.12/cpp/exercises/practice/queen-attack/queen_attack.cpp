#include "queen_attack.h"

#include <sstream>
#include <stdexcept>

namespace queen_attack
{

namespace
{
constexpr std::int32_t board_size{8};
} // unnamed namespace

void chess_board::validate_position(chess_board::position pos)
{
    if((pos.first < 0) || (pos.second < 0)
       || (pos.first >= board_size) || (pos.second >= board_size))
    {
        throw std::domain_error("Position out of bounds");
    }
}

chess_board::chess_board(position white, position black)
    : m_white{white},
      m_black{black}
{
    validate_position(white);
    validate_position(black);

    if((white.first == black.first) && (white.second == black.second))
    {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

chess_board::position chess_board::white() const noexcept
{
    return m_white;
}

chess_board::position chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    if(m_white.first == m_black.first)
    {
        return true;
    }

    if(m_white.second == m_black.second)
    {
        return true;
    }

    const std::int32_t row_diff{(m_white.first > m_black.first)
                                 ? (m_white.first - m_black.first)
                                 : (m_black.first - m_white.first)};

    const std::int32_t col_diff{(m_white.second > m_black.second)
                                 ? (m_white.second - m_black.second)
                                 : (m_black.second - m_white.second)};

    return row_diff == col_diff;
}

chess_board::operator std::string() const
{
    std::ostringstream os;

    for(std::int32_t row{0}; row < board_size; ++row)
    {
        for(std::int32_t col{0}; col < board_size; ++col)
        {
            if((row == m_white.first) && (col == m_white.second))
            {
                os << 'W';
            }
            else if((row == m_black.first) && (col == m_black.second))
            {
                os << 'B';
            }
            else
            {
                os << '_';
            }

            if(col < (board_size - 1))
            {
                os << ' ';
            }
        }

        if(row < (board_size - 1))
        {
            os << '\n';
        }
    }

    return os.str();
}

} // namespace queen_attack
