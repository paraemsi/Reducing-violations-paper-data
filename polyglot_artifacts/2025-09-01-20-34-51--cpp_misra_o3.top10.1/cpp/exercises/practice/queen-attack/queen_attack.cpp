#include "queen_attack.h"

namespace queen_attack {

constexpr bool chess::is_valid_position(position_t pos) noexcept
{
    return ((pos.first  >= static_cast<coordinate_t>(0)) &&
            (pos.first  <  static_cast<coordinate_t>(8)) &&
            (pos.second >= static_cast<coordinate_t>(0)) &&
            (pos.second <  static_cast<coordinate_t>(8)));
}

chess::chess(position_t white_pos, position_t black_pos)
    : white_position_{white_pos},
      black_position_{black_pos}
{
    if ((!is_valid_position(white_pos)) || (!is_valid_position(black_pos)) || (white_pos == black_pos))
    {
        throw std::domain_error("Invalid queen position");
    }
}

position_t chess::white() const noexcept
{
    return white_position_;
}

position_t chess::black() const noexcept
{
    return black_position_;
}

bool chess::can_attack() const noexcept
{
    const delta_t row_diff =
        static_cast<delta_t>(white_position_.first) -
        static_cast<delta_t>(black_position_.first);

    const delta_t col_diff =
        static_cast<delta_t>(white_position_.second) -
        static_cast<delta_t>(black_position_.second);

    return ((row_diff == static_cast<delta_t>(0)) ||
            (col_diff == static_cast<delta_t>(0)) ||
            (row_diff == col_diff) ||
            (row_diff == static_cast<delta_t>(-col_diff)));
}

}  // namespace queen_attack
