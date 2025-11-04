#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

using coordinate_t = std::int32_t;
using position_t   = std::pair<coordinate_t, coordinate_t>;

class chess_board
{
public:
    chess_board(position_t white_pos = {0, 3}, position_t black_pos = {7, 3});

    [[nodiscard]] position_t white() const noexcept;
    [[nodiscard]] position_t black() const noexcept;

    [[nodiscard]] bool can_attack() const noexcept;

    /* implicit conversion to printable board */
    // NOLINTNEXTLINE(google-explicit-constructor)
    explicit operator std::string() const;

private:
    position_t m_white;
    position_t m_black;

    static void validate_position(const position_t& pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
