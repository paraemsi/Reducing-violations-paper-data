#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cstdlib> // for std::abs

namespace queen_attack {

namespace {
    constexpr int board_size = 8;

    inline bool in_bounds(const std::pair<int, int>& p) {
        return p.first >= 0 && p.first < board_size && p.second >= 0 && p.second < board_size;
    }
}

chess_board::chess_board()
    : white_{0, 3}, black_{7, 3} {
    // default positions correspond to d1 (white) and d8 (black) in 0-indexed coordinates
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {
    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error{"queen positions must be on the board"};
    }
    if (white_ == black_) {
        throw std::domain_error{"queens cannot occupy the same position"};
    }
}

std::pair<int, int> chess_board::white() const {
    return white_;
}

std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // same row or same column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    // same diagonal
    return std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::ostringstream oss;
    for (int r = 0; r < board_size; ++r) {
        for (int c = 0; c < board_size; ++c) {
            char ch = '_';
            if (r == white_.first && c == white_.second) {
                ch = 'W';
            } else if (r == black_.first && c == black_.second) {
                ch = 'B';
            }
            oss << ch;
            if (c < board_size - 1) {
                oss << ' ';
            }
        }
        if (r < board_size - 1) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace queen_attack
