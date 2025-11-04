#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <string>

namespace queen_attack {

using square_t = std::pair<int, int>;   // {row, column}, zero-indexed

class chess_board {
public:
    // default positions: white (row 0, col 3) – black (row 7, col 3)
    chess_board(square_t white = {0, 3}, square_t black = {7, 3});

    square_t white() const noexcept { return white_; }
    square_t black() const noexcept { return black_; }

    // true if the two queens can attack each other
    bool can_attack() const noexcept;

    // ASCII representation of the board (row 0 is the first line)
    std::string board() const;

private:
    square_t white_;
    square_t black_;

    static bool in_bounds(const square_t& pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
