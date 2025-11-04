#include "queen_attack.h"

#include <cmath>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(const position_t& white, const position_t& black)
    : white_{white}, black_{black} {
    if ((std::get<row_idx>(white_) < 0) || (std::get<row_idx>(white_) > 7) ||
        (std::get<col_idx>(white_) < 0) || (std::get<col_idx>(white_) > 7) ||
        (std::get<row_idx>(black_) < 0) || (std::get<row_idx>(black_) > 7) ||
        (std::get<col_idx>(black_) < 0) || (std::get<col_idx>(black_) > 7)) {
        throw std::domain_error("Queen position out of bounds.");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot be on the same square.");
    }
}

const position_t& chess_board::white() const {
    return white_;
}

const position_t& chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    const std::int32_t col_diff = std::get<col_idx>(white_) - std::get<col_idx>(black_);
    const std::int32_t row_diff = std::get<row_idx>(white_) - std::get<row_idx>(black_);

    return ((std::get<col_idx>(white_) == std::get<col_idx>(black_)) ||
            (std::get<row_idx>(white_) == std::get<row_idx>(black_)) ||
            (std::abs(col_diff) == std::abs(row_diff)));
}

}  // namespace queen_attack
