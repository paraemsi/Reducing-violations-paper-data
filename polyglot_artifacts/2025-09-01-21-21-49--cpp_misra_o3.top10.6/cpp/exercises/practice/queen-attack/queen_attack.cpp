#include "queen_attack.h"

#include <stdexcept>

namespace queen_attack {

namespace {

constexpr queen_attack::chess_board::coordinate_t board_size{8};

} // anonymous namespace


// ----------  private helpers -------------------------------------------------
bool chess_board::is_valid(position_t pos)
{
    /* position is valid only if both coordinates are within [0, board_size) */
    return (pos.first  >= 0) &&
           (pos.first  <  board_size) &&
           (pos.second >= 0) &&
           (pos.second <  board_size);
}

// ----------  ctors -----------------------------------------------------------
chess_board::chess_board(position_t white, position_t black)
    : m_white{white},
      m_black{black}
{
    if (!is_valid(m_white) || !is_valid(m_black)) {
        throw std::domain_error{"Queen position is out of bounds"};
    }

    if ((m_white.first == m_black.first) &&
        (m_white.second == m_black.second)) {
        throw std::domain_error{"Queens cannot occupy the same position"};
    }
}

// ----------  accessors -------------------------------------------------------
chess_board::position_t chess_board::white() const
{
    return m_white;
}

chess_board::position_t chess_board::black() const
{
    return m_black;
}

// ----------  rule logic ------------------------------------------------------
bool chess_board::can_attack() const
{
    const bool same_row { (m_white.first == m_black.first) };
    const bool same_col { (m_white.second == m_black.second) };

    const coordinate_t row_diff{
        (m_white.first >= m_black.first)
            ? (m_white.first - m_black.first)
            : (m_black.first - m_white.first) };

    const coordinate_t col_diff{
        (m_white.second >= m_black.second)
            ? (m_white.second - m_black.second)
            : (m_black.second - m_white.second) };

    const bool same_diag { row_diff == col_diff };

    return same_row || same_col || same_diag;
}

}  // namespace queen_attack
