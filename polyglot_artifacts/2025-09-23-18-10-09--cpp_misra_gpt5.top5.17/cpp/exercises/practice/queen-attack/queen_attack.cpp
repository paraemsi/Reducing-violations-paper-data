#include "queen_attack.h"
#include <cstdint>
#include <stdexcept>

namespace {

constexpr std::int32_t zero_i32 = static_cast<std::int32_t>(0);

constexpr std::int32_t abs_i32(std::int32_t v) noexcept
{
    return ((v < zero_i32) ? (-v) : v);
}

bool can_attack_impl(queen_attack::position const& white, queen_attack::position const& black) noexcept
{
    const std::int32_t wr = static_cast<std::int32_t>(white.second);
    const std::int32_t wc = static_cast<std::int32_t>(white.first);
    const std::int32_t br = static_cast<std::int32_t>(black.second);
    const std::int32_t bc = static_cast<std::int32_t>(black.first);

    const bool same_row = (wr == br);
    const bool same_col = (wc == bc);
    const bool same_diag = (abs_i32((wr - br)) == abs_i32((wc - bc)));

    return ((same_row || same_col) || same_diag);
}

}  // unnamed namespace

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}
    , black_{black}
{
    // Validate positions: cannot be equal and must be on board [0,7]
    if ((white_ == black_)) {
        throw std::domain_error("queens cannot share the same position");
    }

    // Check both coordinates are within 0..7 inclusive
    auto in_range = [](std::int32_t v) noexcept -> bool {
        return ((v >= static_cast<std::int32_t>(0)) && (v <= static_cast<std::int32_t>(7)));
    };

    if ((!in_range(white_.first)) || (!in_range(white_.second)) || (!in_range(black_.first)) || (!in_range(black_.second))) {
        throw std::domain_error("position out of bounds");
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
    return can_attack_impl(white_, black_);
}


}  // namespace queen_attack
