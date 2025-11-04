#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

queen::queen(const std::pair<int, int>& position) : pos_(position) {
    if (position.first < 0 || position.first > 7 ||
        position.second < 0 || position.second > 7) {
        throw std::domain_error("Queen position must be on a 8x8 board");
    }
}

std::pair<int, int> queen::position() const {
    return pos_;
}

static bool queens_can_attack(const std::pair<int, int>& w, const std::pair<int, int>& b) {
    int x1 = w.first, y1 = w.second;
    int x2 = b.first, y2 = b.second;
    if (x1 == x2) return true;
    if (y1 == y2) return true;
    if (std::abs(x1 - x2) == std::abs(y1 - y2)) return true;
    return false;
}

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_queen_(white), black_queen_(black) {
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_queen_.position();
}

std::pair<int, int> chess_board::black() const {
    return black_queen_.position();
}

bool chess_board::can_attack() const {
    return queens_can_attack(white_queen_.position(), black_queen_.position());
}

}  // namespace queen_attack
