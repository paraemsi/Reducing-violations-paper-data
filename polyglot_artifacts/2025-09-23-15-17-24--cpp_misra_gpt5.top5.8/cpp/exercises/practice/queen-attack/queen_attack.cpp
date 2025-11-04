#include "queen_attack.h"

#include <stdexcept>
#include <cstdint>

namespace queen_attack {

constexpr coord_t board_size = static_cast<coord_t>(8);

static bool is_valid(const position& p)
{
    return ((p.first >= static_cast<coord_t>(0)) && (p.first < board_size) && (p.second >= static_cast<coord_t>(0)) && (p.second < board_size));
}

chess_board::chess_board(const position& white, const position& black)
    : white_(white), black_(black)
{
    if ((!is_valid(white_)) || (!is_valid(black_))) {
        throw std::domain_error("invalid position");
    }

    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const
{
    return std::pair<int, int>{static_cast<int>(white_.first), static_cast<int>(white_.second)};
}

std::pair<int, int> chess_board::black() const
{
    return std::pair<int, int>{static_cast<int>(black_.first), static_cast<int>(black_.second)};
}

bool chess_board::can_attack() const
{
    return queen_attack::can_attack(white_, black_);
}

bool can_attack(const position& white, const position& black)
{
    if ((!is_valid(white)) || (!is_valid(black))) {
        throw std::domain_error("invalid position");
    }

    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("queens cannot occupy the same position");
    }

    const bool same_row = (white.first == black.first);
    const bool same_col = (white.second == black.second);

    const std::int32_t dr = (white.first - black.first);
    const std::int32_t dc = (white.second - black.second);

    const std::int32_t adr = ((dr < static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(-dr) : dr);
    const std::int32_t adc = ((dc < static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(-dc) : dc);

    const bool same_diag = (adr == adc);

    return (same_row || (same_col || same_diag));
}

}  // namespace queen_attack
