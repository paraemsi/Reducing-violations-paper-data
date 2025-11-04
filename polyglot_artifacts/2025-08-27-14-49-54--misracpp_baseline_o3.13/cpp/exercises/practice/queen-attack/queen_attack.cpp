#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cstdlib>

namespace queen_attack {

namespace {
constexpr int board_size{8};
}

// ---- helper --------------------------------------------------------------

bool chess_board::is_valid(const std::pair<int, int>& pos)
{
    return pos.first >= 0 && pos.first < board_size &&
           pos.second >= 0 && pos.second < board_size;
}

// ---- ctor ----------------------------------------------------------------

chess_board::chess_board(std::pair<int, int> white,
                         std::pair<int, int> black)
    : white_{white}, black_{black}
{
    if (!is_valid(white_) || !is_valid(black_) || white_ == black_) {
        throw std::domain_error{"Invalid queen position"};
    }
}

// ---- accessors -----------------------------------------------------------

std::pair<int, int> chess_board::white() const
{
    return white_;
}

std::pair<int, int> chess_board::black() const
{
    return black_;
}

// ---- string conversion ---------------------------------------------------

chess_board::operator std::string() const
{
    std::ostringstream oss;

    for (int row = 0; row < board_size; ++row) {
        for (int col = 0; col < board_size; ++col) {
            char square = '_';
            if (white_.first == row && white_.second == col) {
                square = 'W';
            } else if (black_.first == row && black_.second == col) {
                square = 'B';
            }
            oss << square;
            if (col < board_size - 1) {
                oss << ' ';
            }
        }
        if (row < board_size - 1) {
            oss << '\n';
        }
    }
    return oss.str();
}

// ---- logic ---------------------------------------------------------------

bool chess_board::can_attack() const
{
    // Same row or same column
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }

    // Same diagonal
    return std::abs(white_.first - black_.first) ==
           std::abs(white_.second - black_.second);
}

} // namespace queen_attack
