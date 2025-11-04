#pragma once

#include <utility>

namespace queen_attack {

class queen {
public:
    queen(int row, int col);
    std::pair<int, int> position() const;
private:
    int row_;
    int col_;
};

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);
    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;
    bool can_attack() const noexcept;
private:
    std::pair<int, int> white_pos_;
    std::pair<int, int> black_pos_;
};

bool can_attack(const queen& q1, const queen& q2) noexcept;

}  // namespace queen_attack
