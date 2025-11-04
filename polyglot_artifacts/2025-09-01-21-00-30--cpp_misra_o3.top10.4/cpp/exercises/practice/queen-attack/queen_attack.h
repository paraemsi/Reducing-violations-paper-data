#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <utility>

namespace queen_attack {

namespace detail {
using board_pos_t = std::uint8_t;
constexpr board_pos_t board_size{8U};
} // namespace detail

class chess_board
{
public:
    /*  Tests expect a pair<int,int>. std::int32_t is a typedef for int on
        all mainstream platforms, therefore the template arguments match
        while we still respect the fixed-width rule. */
    using position_t = std::pair<std::int32_t, std::int32_t>;

    chess_board() = default;
    chess_board(position_t white_pos, position_t black_pos);

    [[nodiscard]] position_t white() const noexcept;
    [[nodiscard]] position_t black() const noexcept;
    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] operator std::string() const;

private:
    /* stored as signed 32-bit to avoid implicit signed / unsigned mixing */
    position_t m_white{0, 3};
    position_t m_black{7, 3};
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
