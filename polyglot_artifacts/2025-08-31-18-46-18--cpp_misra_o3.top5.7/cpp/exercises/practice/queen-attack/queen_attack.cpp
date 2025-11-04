#include "queen_attack.h"

#include <sstream>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(const position_t& white, const position_t& black)
    : white_pos_{}, black_pos_{} {
    if ((!is_valid_position_int(white)) || (!is_valid_position_int(black))) {
        throw std::domain_error("Invalid position");
    }
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same square");
    }

    /* conversion validated – values are in range 0-7 */
    white_pos_ = board_position_t{static_cast<coord_t>(white.first), static_cast<coord_t>(white.second)};
    black_pos_ = board_position_t{static_cast<coord_t>(black.first), static_cast<coord_t>(black.second)};
}

chess_board::position_t chess_board::white() const noexcept {
    return {static_cast<int>(white_pos_.first), static_cast<int>(white_pos_.second)};
}

chess_board::position_t chess_board::black() const noexcept {
    return {static_cast<int>(black_pos_.first), static_cast<int>(black_pos_.second)};
}

bool chess_board::can_attack() const noexcept {
    /* Same row */
    if (white_pos_.first == black_pos_.first) {
        return true;
    }

    /* Same column */
    if (white_pos_.second == black_pos_.second) {
        return true;
    }

    /* Same diagonal */
    const coord_t row_diff =
        (white_pos_.first > black_pos_.first)
            ? static_cast<coord_t>(white_pos_.first - black_pos_.first)
            : static_cast<coord_t>(black_pos_.first - white_pos_.first);

    const coord_t col_diff =
        (white_pos_.second > black_pos_.second)
            ? static_cast<coord_t>(white_pos_.second - black_pos_.second)
            : static_cast<coord_t>(black_pos_.second - white_pos_.second);

    return (row_diff == col_diff);
}

chess_board::operator std::string() const {
    std::ostringstream out;

    for (coord_t row = static_cast<coord_t>(0U); row < static_cast<coord_t>(8U); ++row) {
        for (coord_t col = static_cast<coord_t>(0U); col < static_cast<coord_t>(8U); ++col) {
            char symbol = '_';

            if ((row == white_pos_.first) && (col == white_pos_.second)) {
                symbol = 'W';
            } else if ((row == black_pos_.first) && (col == black_pos_.second)) {
                symbol = 'B';
            }

            out << symbol;
            if (col < static_cast<coord_t>(7U)) {
                out << ' ';
            }
        }
        if (row < static_cast<coord_t>(7U)) {
            out << '\n';
        }
    }

    return out.str();
}

bool chess_board::is_valid_position(const board_position_t& pos) noexcept {
    return (pos.first < static_cast<coord_t>(8U)) && (pos.second < static_cast<coord_t>(8U));
}

bool chess_board::is_valid_position_int(const position_t& pos) noexcept {
    return ((pos.first >= 0) && (pos.first < 8) && (pos.second >= 0) && (pos.second < 8));
}

}  // namespace queen_attack
