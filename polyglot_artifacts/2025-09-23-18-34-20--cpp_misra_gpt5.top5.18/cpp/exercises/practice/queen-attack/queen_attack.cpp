#include "queen_attack.h"

#include <ostream>
#include <stdexcept>

namespace queen_attack {

namespace {
    inline bool is_valid_position(const position& p) noexcept
    {
        return (((p.first >= 0) && (p.second >= 0)) &&
                ((p.first < static_cast<int>(8)) && (p.second < static_cast<int>(8))));
    }
}  // unnamed namespace

chess_board::chess_board(position white, position black)
    : white_pos(white)
    , black_pos(black)
{
    if ((!is_valid_position(white_pos)) || (!is_valid_position(black_pos))) {
        throw std::domain_error("invalid position");
    } else {
        // ok
    }

    if ((white_pos.first == black_pos.first) && (white_pos.second == black_pos.second)) {
        throw std::domain_error("queens cannot occupy the same position");
    } else {
        // ok
    }
}

position chess_board::white() const noexcept
{
    return white_pos;
}

position chess_board::black() const noexcept
{
    return black_pos;
}

bool chess_board::can_attack() const noexcept
{
    const std::int32_t wr = static_cast<std::int32_t>(white_pos.first);
    const std::int32_t wc = static_cast<std::int32_t>(white_pos.second);
    const std::int32_t br = static_cast<std::int32_t>(black_pos.first);
    const std::int32_t bc = static_cast<std::int32_t>(black_pos.second);

    const std::int32_t dr = (wr > br) ? (wr - br) : (br - wr);
    const std::int32_t dc = (wc > bc) ? (wc - bc) : (bc - wc);

    return ((wr == br) || (wc == bc) || (dr == dc));
}

std::ostream& operator<<(std::ostream& os, const chess_board& board)
{
    for (coord_t r = static_cast<coord_t>(0U); r < static_cast<coord_t>(8U); ++r) {
        for (coord_t c = static_cast<coord_t>(0U); c < static_cast<coord_t>(8U); ++c) {
            char ch = '_';
            if ((board.white().first == r) && (board.white().second == c)) {
                ch = 'W';
            } else if ((board.black().first == r) && (board.black().second == c)) {
                ch = 'B';
            } else {
                ch = '_';
            }

            os << ch;

            if (c < static_cast<coord_t>(7U)) {
                os << ' ';
            } else {
                // no trailing space at line end
            }
        }

        if (r < static_cast<coord_t>(7U)) {
            os << '\n';
        } else {
            // no trailing newline at end of board
        }
    }

    return os;
}

}  // namespace queen_attack
