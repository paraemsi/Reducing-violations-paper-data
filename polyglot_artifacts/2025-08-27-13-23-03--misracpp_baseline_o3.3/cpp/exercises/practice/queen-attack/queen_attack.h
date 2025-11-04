#ifndef QUEEN_ATTACK_H
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    // Defaults follow the Exercism reference implementation.
    chess_board(std::pair<int, int> white_pos = {0, 3},
                std::pair<int, int> black_pos = {7, 3});

    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;

    // True when the two queens threaten one another.
    bool can_attack() const noexcept;

    // 8 × 8 board visualisation.
    explicit operator std::string() const;

private:
    std::pair<int, int> white_pos_;
    std::pair<int, int> black_pos_;
};

}  // namespace queen_attack

#endif  // QUEEN_ATTACK_H
