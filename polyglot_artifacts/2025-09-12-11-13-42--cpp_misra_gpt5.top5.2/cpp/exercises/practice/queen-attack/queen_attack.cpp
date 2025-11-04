#include "queen_attack.h"

#include <cstdint>
#include <string>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board() noexcept
    : white_{position{static_cast<coord_t>(0), static_cast<coord_t>(3)}}
    , black_{position{static_cast<coord_t>(7), static_cast<coord_t>(3)}} {
}

chess_board::chess_board(position white, position black)
    : white_{white}
    , black_{black} {
    const bool white_row_ok = (white.row < static_cast<coord_t>(8));
    const bool white_col_ok = (white.column < static_cast<coord_t>(8));
    const bool black_row_ok = (black.row < static_cast<coord_t>(8));
    const bool black_col_ok = (black.column < static_cast<coord_t>(8));

    if (!(white_row_ok && white_col_ok && black_row_ok && black_col_ok)) {
        throw std::domain_error("Queen position must be within [0,7] for row and column");
    } else {
        // positions are in range
    }

    if ((white.row == black.row) && (white.column == black.column)) {
        throw std::domain_error("Queens cannot occupy the same position");
    } else {
        // positions are valid and not overlapping
    }
}

position chess_board::white() const noexcept {
    return white_;
}

position chess_board::black() const noexcept {
    return black_;
}

bool chess_board::can_attack() const noexcept {
    const bool same_row = (white_.row == black_.row);
    const bool same_column = (white_.column == black_.column);

    const std::uint32_t wr = static_cast<std::uint32_t>(white_.row);
    const std::uint32_t br = static_cast<std::uint32_t>(black_.row);
    const std::uint32_t wc = static_cast<std::uint32_t>(white_.column);
    const std::uint32_t bc = static_cast<std::uint32_t>(black_.column);

    const std::uint32_t dr = (wr > br) ? (wr - br) : (br - wr);
    const std::uint32_t dc = (wc > bc) ? (wc - bc) : (bc - wc);

    const bool same_diagonal = (dr == dc);

    return ((same_row) || (same_column) || (same_diagonal));
}

chess_board::operator std::string() const {
    std::string out;

    for (coord_t r = static_cast<coord_t>(0); r < static_cast<coord_t>(8); ++r) {
        for (coord_t c = static_cast<coord_t>(0); c < static_cast<coord_t>(8); ++c) {
            char cell = '_';

            if ((white_.row == r) && (white_.column == c)) {
                cell = 'W';
            } else {
                if ((black_.row == r) && (black_.column == c)) {
                    cell = 'B';
                } else {
                    // keep '_'
                }
            }

            out.push_back(cell);

            if (c < static_cast<coord_t>(7)) {
                out.push_back(' ');
            } else {
                // no trailing space at end of line
            }
        }

        if (r < static_cast<coord_t>(7)) {
            out.push_back('\n');
        } else {
            // no trailing newline at end of board
        }
    }

    return out;
}

}  // namespace queen_attack
