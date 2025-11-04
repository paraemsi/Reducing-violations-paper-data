#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

using position = std::pair<std::int32_t, std::int32_t>;

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

bool can_attack(const position& white_pos, const position& black_pos) noexcept;

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
