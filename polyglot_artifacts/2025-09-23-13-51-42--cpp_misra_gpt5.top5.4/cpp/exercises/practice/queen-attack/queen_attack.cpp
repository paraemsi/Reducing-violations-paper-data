#include "queen_attack.h"

#include <stdexcept>

namespace queen_attack {

namespace {
    // Helper to determine if two positions are in attacking diagonal relation
    bool same_diagonal(const position& lhs, const position& rhs) noexcept
    {
        const std::int32_t drow = static_cast<std::int32_t>(lhs.first - rhs.first);
        const std::int32_t dcol = static_cast<std::int32_t>(lhs.second - rhs.second);
        return ((drow == dcol) || (drow == static_cast<std::int32_t>(-dcol)));
    }
}  // namespace

chess_board::chess_board(position white, position black)
    : white_{white}
    , black_{black}
{
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position chess_board::white() const noexcept
{
    return white_;
}

position chess_board::black() const noexcept
{
    return black_;
}

bool chess_board::can_attack() const noexcept
{
    return (::queen_attack::can_attack(white_, black_));
}

bool can_attack(const position& white_pos, const position& black_pos) noexcept
{
    const bool same_row = (white_pos.first == black_pos.first);
    const bool same_col = (white_pos.second == black_pos.second);
    const bool diag = same_diagonal(white_pos, black_pos);

    return (same_row || same_col || diag);
}

}  // namespace queen_attack
