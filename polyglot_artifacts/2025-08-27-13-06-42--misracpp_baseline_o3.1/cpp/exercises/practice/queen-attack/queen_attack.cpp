#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cstdlib>

namespace queen_attack {

namespace {
constexpr int board_size = 8;

bool is_on_board(const std::pair<int, int>& pos) {
    return pos.first >= 0 && pos.first < board_size &&
           pos.second >= 0 && pos.second < board_size;
}
}  // namespace

chess_board::chess_board(std::pair<int, int> white_pos,
                         std::pair<int, int> black_pos)
    : white_{white_pos}, black_{black_pos} {

    if (!is_on_board(white_) || !is_on_board(black_)) {
        throw std::domain_error{"Queen must be placed on the board"};
    }
    if (white_ == black_) {
        throw std::domain_error{"Queens cannot share the same space"};
    }
}

std::pair<int, int> chess_board::white() const {
    return white_;
}

std::pair<int, int> chess_board::black() const {
    return black_;
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
            if (c < board_size - 1) {
                os << ' ';
            }
        }
        if (r < board_size - 1) {
            os << '\n';
        }
    }
    return os.str();
}

bool chess_board::can_attack() const {
    // Same row
    if (white_.first == black_.first) return true;
    // Same column
    if (white_.second == black_.second) return true;
    // Same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

}  // namespace queen_attack
