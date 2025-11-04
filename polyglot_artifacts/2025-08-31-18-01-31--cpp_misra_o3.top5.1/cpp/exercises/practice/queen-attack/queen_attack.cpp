#include "queen_attack.h"

#include <stdexcept>   // std::domain_error
#include <cmath>       // std::abs

namespace queen_attack {

// ======== constructor ======================================================
chess_board::chess_board(const position_t white, const position_t black)
    : m_white{white}
    , m_black{black}
{
    const auto in_bounds = [](const coordinate_t coord) noexcept -> bool {
        return ((coord >= static_cast<coordinate_t>(0)) &&
                (coord < static_cast<coordinate_t>(8)));
    };

    if ((!in_bounds(m_white.first)) || (!in_bounds(m_white.second)) ||
        (!in_bounds(m_black.first)) || (!in_bounds(m_black.second))) {
        throw std::domain_error{"Queen position out of bounds"};
    }

    if ((m_white.first == m_black.first) &&
        (m_white.second == m_black.second)) {
        throw std::domain_error{"Queens may not occupy the same square"};
    }
}

// ======== accessors ========================================================
position_t chess_board::white() const noexcept
{
    return m_white;
}

position_t chess_board::black() const noexcept
{
    return m_black;
}

// ======== attack test ======================================================
bool chess_board::can_attack() const noexcept
{
    const auto same_row = (m_white.first == m_black.first);
    const auto same_column = (m_white.second == m_black.second);
    const auto same_diagonal =
        (std::abs(m_white.first  - m_black.first) ==
         std::abs(m_white.second - m_black.second));

    return (same_row || same_column || same_diagonal);
}

// ======== board visualisation =============================================
std::string chess_board::board_representation() const noexcept
{
    std::string board{};
    board.reserve((8U * ((2U * 8U) - 1U)) + 7U);   // rough pre-allocation

    for (coordinate_t row = static_cast<coordinate_t>(0);
         row < static_cast<coordinate_t>(8);
         ++row) {
        for (coordinate_t col = static_cast<coordinate_t>(0);
             col < static_cast<coordinate_t>(8);
             ++col) {
            char square{'O'};
            if ((m_white.first == row) && (m_white.second == col)) {
                square = 'W';
            } else if ((m_black.first == row) && (m_black.second == col)) {
                square = 'B';
            }

            board.push_back(square);
            if (col != static_cast<coordinate_t>(7)) {
                board.push_back(' ');
            }
        }
        if (row != static_cast<coordinate_t>(7)) {
            board.push_back('\n');
        }
    }
    return board;
}

chess_board::operator std::string() const noexcept
{
    return board_representation();
}

}   // namespace queen_attack
