#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

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

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    std::pair<int, int> white_pos_;
    std::pair<int, int> black_pos_;
};

bool can_attack(const queen& q1, const queen& q2);

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
