#include "queen_attack.h"

#include <sstream>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black} {
    const auto in_bounds = [](const position& p) -> bool {
        const std::int32_t zero = static_cast<std::int32_t>(0);
        const std::int32_t seven = static_cast<std::int32_t>(7);
        return ((p.first >= zero) && (p.first <= seven) && (p.second >= zero) && (p.second <= seven));
    };

    if ((!in_bounds(white_)) || (!in_bounds(black_))) {
        throw std::domain_error("Queen position must be on the board");
    }

    if ((white_.first == black_.first) && (white_.second == black_.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position chess_board::white() const {
    return white_;
}

position chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    const bool same_row = (white_.first == black_.first);
    const bool same_col = (white_.second == black_.second);

    const std::int32_t delta_row = (white_.first - black_.first);
    const std::int32_t delta_col = (white_.second - black_.second);
    const std::int32_t abs_delta_row = ((delta_row < static_cast<std::int32_t>(0)) ? (-delta_row) : delta_row);
    const std::int32_t abs_delta_col = ((delta_col < static_cast<std::int32_t>(0)) ? (-delta_col) : delta_col);
    const bool same_diag = (abs_delta_row == abs_delta_col);

    return (same_row || same_col || same_diag);
}

chess_board::operator std::string() const {
    std::ostringstream os;
    for (std::int32_t r = 0; r < 8; ++r) {
        for (std::int32_t c = 0; c < 8; ++c) {
            char ch = 'O';
            if ((white_.first == r) && (white_.second == c)) {
                ch = 'W';
            } else {
                if ((black_.first == r) && (black_.second == c)) {
                    ch = 'B';
                }
            }

            os << ch;
            if (c < 7) {
                os << ' ';
            }
        }
        if (r < 7) {
            os << '\n';
        }
    }
    return os.str();
}

}  // namespace queen_attack
