#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <sstream>

namespace queen_attack {

bool chess_board::is_valid(const std::pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < chess_board::kBoardSize &&
           pos.second >= 0 && pos.second < chess_board::kBoardSize;
}

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : white_pos_{white}, black_pos_{black}
{
    if (!is_valid(white) || !is_valid(black)) {
        throw std::domain_error("Queen position out of the board");
    }
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

std::pair<int,int> chess_board::white() const {
    return white_pos_;
}

std::pair<int,int> chess_board::black() const {
    return black_pos_;
}

bool chess_board::can_attack() const {
    if (white_pos_.first == black_pos_.first) return true;              // same row
    if (white_pos_.second == black_pos_.second) return true;            // same column
    if (std::abs(white_pos_.first - black_pos_.first) ==
        std::abs(white_pos_.second - black_pos_.second)) return true;   // diagonal
    return false;
}

std::string chess_board::to_string() const {
    std::ostringstream out;
    for (int row = 0; row < chess_board::kBoardSize; ++row) {
        for (int col = 0; col < chess_board::kBoardSize; ++col) {
            if (row == white_pos_.first && col == white_pos_.second) {
                out << 'W';
            } else if (row == black_pos_.first && col == black_pos_.second) {
                out << 'B';
            } else {
                out << '_';
            }
            if (col != chess_board::kBoardSize - 1) {
                out << ' ';
            }
        }
        if (row != chess_board::kBoardSize - 1) {
            out << '\n';
        }
    }
    return out.str();
}

}  // namespace queen_attack
