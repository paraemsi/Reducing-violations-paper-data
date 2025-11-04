#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

typedef std::pair<int, int> position;

class chess_board {
public:
    chess_board(position white_pos = position(0, 3), position black_pos = position(7, 3));
    position white() const;
    position black() const;
    bool can_attack() const;

private:
    position white_;
    position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
