#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>
#include <iosfwd>

namespace queen_attack {

using coord_t = std::uint8_t;
using position = std::pair<int, int>;

class chess_board {
public:
    chess_board(position white = position{0, 3},
                position black = position{7, 3});

    position white() const noexcept;
    position black() const noexcept;

    bool can_attack() const noexcept;

private:
    position white_pos;
    position black_pos;
};

std::ostream& operator<<(std::ostream& os, const chess_board& board);

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
