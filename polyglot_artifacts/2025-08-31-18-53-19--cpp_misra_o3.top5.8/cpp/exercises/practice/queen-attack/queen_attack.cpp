#include "queen_attack.h"

#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos_{static_cast<chess_board::coord_t>(white.first),
                 static_cast<chess_board::coord_t>(white.second)},
      black_pos_{static_cast<chess_board::coord_t>(black.first),
                 static_cast<chess_board::coord_t>(black.second)} {
    if (white == black) {
        throw std::domain_error("Invalid queen position");
    }
    if ((!is_position_valid(white_pos_)) || (!is_position_valid(black_pos_))) {
        throw std::domain_error("Invalid queen position");
    }
}

std::pair<int, int> chess_board::white() const noexcept {
    return {static_cast<int>(white_pos_.first), static_cast<int>(white_pos_.second)};
}

std::pair<int, int> chess_board::black() const noexcept {
    return {static_cast<int>(black_pos_.first), static_cast<int>(black_pos_.second)};
}

bool chess_board::can_attack() const noexcept {
    const chess_board::coord_t col_diff{white_pos_.first - black_pos_.first};
    const chess_board::coord_t row_diff{white_pos_.second - black_pos_.second};

    if ((col_diff == 0) || (row_diff == 0)) {
        return true;
    }

    return (std::abs(col_diff) == std::abs(row_diff));
}

bool chess_board::is_position_valid(const std::pair<chess_board::coord_t, chess_board::coord_t>& pos) noexcept {
    return ((pos.first >= board_min_) && (pos.first <= board_max_) &&
            (pos.second >= board_min_) && (pos.second <= board_max_));
}

}  // namespace queen_attack
