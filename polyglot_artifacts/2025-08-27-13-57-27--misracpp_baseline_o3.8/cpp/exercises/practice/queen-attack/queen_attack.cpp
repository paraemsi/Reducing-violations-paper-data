#include "queen_attack.h"

#include <sstream>
#include <cmath>

namespace queen_attack {

static bool position_invalid(const std::pair<int,int>& pos) {
    return pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7;
}

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_{white}, black_{black}
{
    if (position_invalid(white) || position_invalid(black) || white == black) {
        throw std::domain_error("Invalid queen positions");
    }
}

bool chess_board::can_attack() const {
    // same row
    if (white_.first == black_.first) return true;
    // same column
    if (white_.second == black_.second) return true;
    // diagonal
    return std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

chess_board::operator std::string() const {
    std::ostringstream out;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (row == white_.first && col == white_.second) {
                out << 'W';
            } else if (row == black_.first && col == black_.second) {
                out << 'B';
            } else {
                out << '_';
            }
            if (col != 7) out << ' ';
        }
        if (row != 7) out << '\n';
    }
    return out.str();
}

}  // namespace queen_attack
