#include "queen_attack.h"

#include <cstdlib>   // std::abs
#include <sstream>

namespace queen_attack {

namespace {
    constexpr int board_min = 0;
    constexpr int board_max = 7;
}

void chess_board::validate_position(const coordinate& pos)
{
    if (((pos.first < board_min) || (pos.first > board_max)) || ((pos.second < board_min) || (pos.second > board_max))) {
        throw std::domain_error("position out of bounds");
    }
}

chess_board::chess_board(const coordinate& white, const coordinate& black)
    : white_(white), black_(black)
{
    validate_position(white_);
    validate_position(black_);
    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

const coordinate& chess_board::white() const noexcept
{
    return white_;
}

const coordinate& chess_board::black() const noexcept
{
    return black_;
}

bool chess_board::can_attack() const noexcept
{
    if ((white_.first == black_.first)) {
        return true;
    }
    if ((white_.second == black_.second)) {
        return true;
    }
    if ((std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second))) {
        return true;
    }
    return false;
}

chess_board::operator std::string() const
{
    std::ostringstream oss;
    for (index_t r = 0; (r <= board_max); ++r) {
        for (index_t c = 0; (c <= board_max); ++c) {
            char cell = '_';
            if ((r == white_.first) && (c == white_.second)) {
                cell = 'W';
            } else {
                if ((r == black_.first) && (c == black_.second)) {
                    cell = 'B';
                } else {
                    // no-op
                }
            }
            oss << cell;
            if ((c < board_max)) {
                oss << ' ';
            } else {
                // no-op
            }
        }
        oss << '\n';
    }
    return oss.str();
}

}  // namespace queen_attack
