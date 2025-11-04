#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack
{

using coordinate_t = std::uint8_t;
using position_t   = std::pair<coordinate_t, coordinate_t>;

class chess_board
{
public:
    chess_board(position_t white_pos = position_t{ static_cast<coordinate_t>(0U), static_cast<coordinate_t>(3U) },
                position_t black_pos = position_t{ static_cast<coordinate_t>(7U), static_cast<coordinate_t>(3U) });

    [[nodiscard]] std::pair<std::int32_t, std::int32_t> white() const;
    [[nodiscard]] std::pair<std::int32_t, std::int32_t> black() const;

    bool can_attack() const;

    explicit operator std::string() const;

private:
    position_t m_white;
    position_t m_black;
};

} // namespace queen_attack

#endif // QUEEN_ATTACK_H
