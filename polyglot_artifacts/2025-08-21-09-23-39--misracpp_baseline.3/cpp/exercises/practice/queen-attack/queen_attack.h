#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

class queen {
public:
    queen(const std::pair<int, int>& position);

    std::pair<int, int> position() const;

private:
    std::pair<int, int> pos_;
};

class chess_board {
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    queen white_queen_;
    queen black_queen_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
