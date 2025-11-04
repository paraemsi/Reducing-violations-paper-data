#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);

    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;

    bool can_attack() const noexcept;

private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
