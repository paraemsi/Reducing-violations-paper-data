#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    // Coordinates are {row, column} with 0 ≤ row, column ≤ 7.
    // Throws std::domain_error if a coordinate is off-board or both queens
    // share the same square.
    chess_board(std::pair<int, int> white_pos = {0, 3},
                std::pair<int, int> black_pos = {7, 3});

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;

    // Returns an 8×8 board representation where empty squares are '_',
    // the white queen is 'W' and the black queen is 'B'.
    operator std::string() const;

    // True if the queens can attack each other.
    bool can_attack() const;

private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
