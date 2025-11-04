#include "queen_attack.h"

#include <cstdint>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_pos_{white}, black_pos_{black} {
    if ((white_pos_.first == black_pos_.first) && (white_pos_.second == black_pos_.second)) {
        throw std::domain_error("Queens cannot occupy the same position.");
    } else {
        // no-op
    }
}

position chess_board::white() const noexcept {
    return white_pos_;
}

position chess_board::black() const noexcept {
    return black_pos_;
}

bool chess_board::can_attack() const noexcept {
    const bool same_row = (white_pos_.first == black_pos_.first);
    const bool same_col = (white_pos_.second == black_pos_.second);

    const std::int32_t wr = white_pos_.first;
    const std::int32_t wc = white_pos_.second;
    const std::int32_t br = black_pos_.first;
    const std::int32_t bc = black_pos_.second;

    const std::int32_t dr = (wr - br);
    const std::int32_t dc = (wc - bc);

    const std::int32_t adr = (dr < static_cast<std::int32_t>(0)) ? (-dr) : dr;
    const std::int32_t adc = (dc < static_cast<std::int32_t>(0)) ? (-dc) : dc;

    const bool same_diag = (adr == adc);

    return ((same_row || same_col) || same_diag);
}

}  // namespace queen_attack
