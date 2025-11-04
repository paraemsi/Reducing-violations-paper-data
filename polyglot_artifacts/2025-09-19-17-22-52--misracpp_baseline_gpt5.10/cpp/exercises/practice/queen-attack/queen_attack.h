#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

using position = std::pair<int, int>;

class chess_board {
public:
    chess_board(position white = position{0, 3}, position black = position{7, 3});
    position white() const noexcept;
    position black() const noexcept;
    bool can_attack() const noexcept;

private:
    position white_;
    position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
