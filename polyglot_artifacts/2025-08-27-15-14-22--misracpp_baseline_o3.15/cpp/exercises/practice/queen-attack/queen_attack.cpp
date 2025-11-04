#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <string>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_{white}, black_{black} {
    auto within_bounds = [](std::pair<int, int> pos) {
        return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
    };

    if (!within_bounds(white_) || !within_bounds(black_)) {
        throw std::domain_error{"Queen position out of bounds"};
    }
    if (white_ == black_) {
        throw std::domain_error{"Queens cannot occupy the same position"};
    }
}

bool chess_board::can_attack() const noexcept {
    bool same_row = white_.first == black_.first;
    bool same_col = white_.second == black_.second;
    bool same_diag = std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
    return same_row || same_col || same_diag;
}

chess_board::operator std::string() const {
    std::string board;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char cell = '_';
            if (white_.first == row && white_.second == col) {
                cell = 'W';
            } else if (black_.first == row && black_.second == col) {
                cell = 'B';
            }
            board.push_back(cell);
            if (col != 7) {
                board.push_back(' ');
            }
        }
        board.push_back('\n');
    }
    return board;
}

}  // namespace queen_attack
