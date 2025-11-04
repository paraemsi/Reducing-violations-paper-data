#include "queen_attack.h"

#include <cstddef>
#include <stdexcept>

namespace queen_attack {

namespace {
constexpr std::int32_t board_min = 0;
constexpr std::int32_t board_max = 7;

static std::int32_t abs_i32(std::int32_t v) noexcept
{
    return (v < 0) ? (-v) : (v);
}
}  // namespace

chess_board::chess_board(position white, position black)
    : white_{white}
    , black_{black}
{
    if ((in_bounds(white_) == false) || (in_bounds(black_) == false)) {
        throw std::domain_error("queen positions must be on the 8x8 board");
    }
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("queens cannot occupy the same square");
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
    const std::int32_t wr = white_.first;
    const std::int32_t wc = white_.second;
    const std::int32_t br = black_.first;
    const std::int32_t bc = black_.second;

    const bool same_row = (wr == br);
    const bool same_col = (wc == bc);
    const bool same_diag = (abs_i32(wr - br) == abs_i32(wc - bc));

    return (same_row || same_col) || same_diag;
}

chess_board::operator std::string() const
{
    std::string out{};
    const std::uint32_t side = (static_cast<std::uint32_t>(board_max) + 1U);
    out.reserve(static_cast<std::size_t>(side * (side * 2U))); // rough reserve

    for (std::int32_t r = board_min; (r <= board_max); ++r) {
        for (std::int32_t c = board_min; (c <= board_max); ++c) {
            char cell = '_';
            if ((white_.first == r) && (white_.second == c)) {
                cell = 'W';
            } else {
                if ((black_.first == r) && (black_.second == c)) {
                    cell = 'B';
                } else {
                    // no-op, keep '_'
                }
            }

            out.push_back(cell);
            if (c < board_max) {
                out.push_back(' ');
            } else {
                // no trailing space on last column
            }
        }
        out.push_back('\n');
    }

    return out;
}

bool chess_board::in_bounds(position pos) noexcept
{
    const bool row_ok = ((pos.first >= board_min) && (pos.first <= board_max));
    const bool col_ok = ((pos.second >= board_min) && (pos.second <= board_max));
    return (row_ok && col_ok);
}

}  // namespace queen_attack
