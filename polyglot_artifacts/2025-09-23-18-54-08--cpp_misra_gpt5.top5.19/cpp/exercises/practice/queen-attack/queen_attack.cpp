#include "queen_attack.h"

#include <cstddef>
#include <stdexcept>

namespace queen_attack {

namespace {
    constexpr std::int32_t board_max_index = std::int32_t{7};

    inline bool is_in_bounds(std::int32_t v) noexcept
    {
        return ((v >= std::int32_t{0}) && (v <= board_max_index));
    }
}  // namespace

chess_board::chess_board(position white, position black)
    : white_{white}
    , black_{black}
{
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("queens cannot occupy the same square");
    }

    if ((!is_in_bounds(white_.first)) || (!is_in_bounds(white_.second)) ||
        (!is_in_bounds(black_.first)) || (!is_in_bounds(black_.second))) {
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
    return (on_same_row(white_, black_) || on_same_column(white_, black_) || on_same_diagonal(white_, black_));
}

bool on_same_row(position a, position b) noexcept
{
    return (a.first == b.first);
}

bool on_same_column(position a, position b) noexcept
{
    return (a.second == b.second);
}

bool on_same_diagonal(position a, position b) noexcept
{
    const std::size_t ar = static_cast<std::size_t>(a.first);
    const std::size_t ac = static_cast<std::size_t>(a.second);
    const std::size_t br = static_cast<std::size_t>(b.first);
    const std::size_t bc = static_cast<std::size_t>(b.second);

    const std::size_t dr = (ar >= br) ? (ar - br) : (br - ar);
    const std::size_t dc = (ac >= bc) ? (ac - bc) : (bc - ac);

    return (dr == dc);
}

chess_board::operator std::string() const
{
    std::string out{};
    out.reserve(static_cast<std::size_t>(8U * 16U));  // approximate

    for (std::size_t r = 0U; r < static_cast<std::size_t>(8U); ++r) {
        for (std::size_t c = 0U; c < static_cast<std::size_t>(8U); ++c) {
            const bool is_white = ((r == static_cast<std::size_t>(white_.first)) && (c == static_cast<std::size_t>(white_.second)));
            const bool is_black = ((r == static_cast<std::size_t>(black_.first)) && (c == static_cast<std::size_t>(black_.second)));

            if (is_white) {
                out.push_back('W');
            } else {
                if (is_black) {
                    out.push_back('B');
                } else {
                    out.push_back('_');
                }
            }

            if (c < static_cast<std::size_t>(7U)) {
                out.push_back(' ');
            }
        }
        out.push_back('\n');
    }

    return out;
}

}  // namespace queen_attack
