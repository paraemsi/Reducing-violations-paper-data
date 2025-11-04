#include "queen_attack.h"

#include <stdexcept>
#include <cstdint>

namespace queen_attack {

namespace {

using coord_t = queen_attack::coord_t;

// Absolute difference between two board indices.
[[nodiscard]] inline coord_t abs_diff(coord_t a,
                                      coord_t b) noexcept
{
    return (a >= b) ? (a - b) : (b - a);
}

} // anonymous namespace

void chess_board::validate_position(const position_t& pos)
{
    /* Valid board squares are 0‥7 on both axes */
    if ((pos.first < 0) || (pos.second < 0) ||
        (pos.first >= 8) || (pos.second >= 8)) {
        throw std::domain_error{"Queen must be placed on the 8x8 board."};
    }
}

chess_board::chess_board(const position_t& white_pos,
                         const position_t& black_pos)
    : m_white{white_pos}
    , m_black{black_pos}
{
    validate_position(m_white);
    validate_position(m_black);

    if (m_white == m_black) {
        throw std::domain_error{"Queens cannot occupy the same position."};
    }
}

chess_board::chess_board()
    : m_white{position_t{0, 3}}
    , m_black{position_t{7, 3}}
{
    // Default positions are known to be valid and distinct.
}

position_t chess_board::white() const noexcept
{
    return m_white;
}

position_t chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    // Same row
    if (m_white.first == m_black.first) {
        return true;
    }

    // Same column
    if (m_white.second == m_black.second) {
        return true;
    }

    // Same diagonal: equal absolute row-column difference
    if (abs_diff(m_white.first, m_black.first) ==
        abs_diff(m_white.second, m_black.second)) {
        return true;
    }

    return false;
}

}  // namespace queen_attack
