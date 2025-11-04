#include "queen_attack.h"
#include <stdexcept>

namespace queen_attack {

namespace {

// Absolute difference for int parameters.
constexpr int abs_diff(int a, int b) noexcept
{
    return (a > b) ? (a - b) : (b - a);
}

// Validate a single coordinate is within [0,7].
constexpr bool is_in_bounds(int v) noexcept
{
    return ((v >= 0) && (v < 8));
}

} // namespace

bool can_attack(const position& white, const position& black)
{
    const bool same_row = (white.first == black.first);
    const bool same_col = (white.second == black.second);
    const int d_row = abs_diff(white.first, black.first);
    const int d_col = abs_diff(white.second, black.second);
    const bool same_diag = (d_row == d_col);

    return ((same_row || same_col) || same_diag);
}

chess_board::chess_board(position white_pos, position black_pos)
    : white_{white_pos}
    , black_{black_pos}
{
    // Validate positions are on the board.
    if ((!is_in_bounds(white_.first)) || (!is_in_bounds(white_.second)) ||
        (!is_in_bounds(black_.first)) || (!is_in_bounds(black_.second))) {
        throw std::domain_error("queen positions must be within [0,7] range");
    }

    // Positions must not overlap.
    if (white_ == black_) {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

position chess_board::white() const
{
    return white_;
}

position chess_board::black() const
{
    return black_;
}

bool chess_board::can_attack() const
{
    return queen_attack::can_attack(white_, black_);
}

chess_board::operator std::string() const
{
    std::string out{};
    out.reserve(static_cast<std::string::size_type>(8U * (8U * 2U) + 7U)); // rough reservation

    for (int r = 0; (r < 8); ++r) {
        for (int c = 0; (c < 8); ++c) {
            char cell = '_';
            if ((white_.first == r) && (white_.second == c)) {
                cell = 'W';
            } else {
                if ((black_.first == r) && (black_.second == c)) {
                    cell = 'B';
                } else {
                    // keep '_'
                }
            }
            out.push_back(cell);
            if (c != 7) {
                out.push_back(' ');
            }
        }
        if (r != 7) {
            out.push_back('\n');
        }
    }
    return out;
}

}  // namespace queen_attack
