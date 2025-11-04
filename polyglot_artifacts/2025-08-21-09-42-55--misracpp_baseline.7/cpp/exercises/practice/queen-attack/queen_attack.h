#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdlib>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);

    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;
    bool can_attack() const noexcept;

private:
    std::pair<int, int> white_pos_;
    std::pair<int, int> black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
