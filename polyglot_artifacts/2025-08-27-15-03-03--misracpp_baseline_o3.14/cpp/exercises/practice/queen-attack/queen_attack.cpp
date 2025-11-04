#include "queen_attack.h"
#include <cmath>
#include <sstream>

namespace queen_attack {

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_{white}, black_{black} {

    auto in_bounds = [](const std::pair<int,int>& pos) {
        return pos.first >= 0 && pos.first < 8 &&
               pos.second >= 0 && pos.second < 8;
    };

    if (!in_bounds(white_) || !in_bounds(black_)) {
        throw std::domain_error("Queen position out of bounds");
    }

    if (white_ == black_) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int,int> chess_board::white() const {
    return white_;
}

std::pair<int,int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // same row
    if (white_.first == black_.first) return true;
    // same column
    if (white_.second == black_.second) return true;
    // diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

std::ostream& operator<<(std::ostream& os, const chess_board& board) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (row == board.white_.first && col == board.white_.second) {
                os << 'W';
            } else if (row == board.black_.first && col == board.black_.second) {
                os << 'B';
            } else {
                os << '_';
            }
            if (col < 7) {
                os << ' ';
            }
        }
        if (row < 7) {
            os << '\n';
        }
    }
    return os;
}

chess_board::operator std::string() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

}  // namespace queen_attack
