#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

using coordinate_t = std::uint8_t;
using position_t   = std::pair<coordinate_t, coordinate_t>;

class chess_board {
public:
    chess_board() noexcept;
    chess_board(std::pair<int, int> white_pos,
                std::pair<int, int> black_pos);

    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;
    bool       can_attack() const noexcept;

private:
    position_t m_white {};
    position_t m_black {};

    static bool is_valid(position_t pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
