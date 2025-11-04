#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

class chess_board
{
public:
    using position = std::pair<std::int32_t, std::int32_t>;
    static constexpr std::int32_t invalid_coord { 255 };

    chess_board(position white_pos = position{ invalid_coord, invalid_coord },
                position black_pos = position{ invalid_coord, invalid_coord });

    [[nodiscard]] position white() const noexcept;
    [[nodiscard]] position black() const noexcept;
    [[nodiscard]] bool can_attack() const noexcept;
    [[nodiscard]] std::string to_string() const;
    operator std::string() const;

private:
    position m_white;
    position m_black;

    [[nodiscard]] static bool are_positions_valid(position pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
