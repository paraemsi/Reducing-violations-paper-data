#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdint>

namespace queen_attack {

using coordinate_t = std::int32_t;
using position = std::pair<coordinate_t, coordinate_t>;

class chess_board {
public:
    chess_board(position white, position black);
    position white() const noexcept;
    position black() const noexcept;
    bool can_attack() const noexcept;

private:
    position white_;
    position black_;
};


}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
