#include "queen_attack.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

bool chess_board::valid_position(const std::pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < chess_board::board_size &&
           pos.second >= 0 && pos.second < chess_board::board_size;
}

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_{white}, black_{black} {
    if (white == black || !valid_position(white) || !valid_position(black)) {
        throw std::domain_error("invalid queen position");
    }
}

std::pair<int,int> chess_board::white() const {
    return white_;
}

std::pair<int,int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    if (white_.first == black_.first) {            // same row
        return true;
    }
    if (white_.second == black_.second) {          // same column
        return true;
    }
    // diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::ostringstream os;
    for (int r = 0; r < board_size; ++r) {
        for (int c = 0; c < board_size; ++c) {
            if (r == white_.first && c == white_.second) {
                os << 'W';
            } else if (r == black_.first && c == black_.second) {
                os << 'B';
            } else {
                os << '_';
            }
            if (c != board_size - 1) {
                os << ' ';
            }
        }
        if (r != board_size - 1) {
            os << '\n';
        }
    }
    return os.str();
}

}  // namespace queen_attack
