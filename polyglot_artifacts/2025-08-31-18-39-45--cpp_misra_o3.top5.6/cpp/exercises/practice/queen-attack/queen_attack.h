#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <array>
#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coord_t    = std::uint8_t;
using position_t = std::array<coord_t, 2U>;

class chess_board
{
public:
    chess_board(std::pair<int, int> white_pos, std::pair<int, int> black_pos);

    [[nodiscard]] std::pair<int, int> white() const noexcept;
    [[nodiscard]] std::pair<int, int> black() const noexcept;
    [[nodiscard]] bool       can_attack() const noexcept;
    explicit                 operator std::string() const;

private:
    position_t m_white {};
    position_t m_black {};
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
