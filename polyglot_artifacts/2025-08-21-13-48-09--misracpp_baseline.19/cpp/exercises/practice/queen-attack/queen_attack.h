#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::pair<int, int>& white_pos, const std::pair<int, int>& black_pos);

    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;
    bool can_attack() const noexcept;

private:
    std::pair<int, int> m_white{};
    std::pair<int, int> m_black{};
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
