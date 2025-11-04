#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cstdlib>  // for std::abs

namespace queen_attack {

chess_board::chess_board(position white, position black)
    : white_(white), black_(black) {
    // Validate positions are on the board (0..7)
    if (white_.first < 0 || white_.first >= 8 ||
        white_.second < 0 || white_.second >= 8 ||
        black_.first < 0 || black_.first >= 8 ||
        black_.second < 0 || black_.second >= 8) {
        throw std::domain_error("Queen position must be on board");
    }
    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

position chess_board::white() const {
    return white_;
}

position chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // Same row or same column
    if (white_.first == black_.first) return true;
    if (white_.second == black_.second) return true;

    // Same diagonal
    int dr = white_.first - black_.first;
    if (dr < 0) dr = -dr;
    int dc = white_.second - black_.second;
    if (dc < 0) dc = -dc;
    return dr == dc;
}

chess_board::operator std::string() const {
    std::ostringstream os;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (c != 0) {
                os << ' ';
            }
            if (white_ == position(r, c)) {
                os << 'W';
            } else if (black_ == position(r, c)) {
                os << 'B';
            } else {
                os << '_';
            }
        }
        if (r != 7) {
            os << '\n';
        }
    }
    return os.str();
}

}  // namespace queen_attack
