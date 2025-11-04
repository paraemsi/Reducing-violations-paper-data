#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdint>

namespace queen_attack {

using position = std::pair<int, int>;

class chess_board {
public:
    chess_board(position white, position black);

    position white() const noexcept;
    position black() const noexcept;

    bool can_attack() const noexcept;

private:
    std::pair<std::int32_t, std::int32_t> white_;
    std::pair<std::int32_t, std::int32_t> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
