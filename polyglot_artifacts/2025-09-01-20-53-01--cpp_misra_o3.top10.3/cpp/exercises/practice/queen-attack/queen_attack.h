#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <stdexcept>
#include <utility>

namespace queen_attack {

using coordinate_t = std::uint8_t;

struct position final
{
    coordinate_t row  {};   // 0 (top) … 7 (bottom)
    coordinate_t col  {};   // 0 (left) … 7 (right)

    /* default, row/col already value-initialised to 0 */
    constexpr position() noexcept = default;

    /* construct from two signed integers (used by unit tests) */
    constexpr position(std::int32_t r, std::int32_t c) noexcept
        : row{ static_cast<coordinate_t>(r) },
          col{ static_cast<coordinate_t>(c) }
    {
        /* range checks are done by chess_board later */
    }

    /* construct from std::pair<int,int> (unit-test helper) – implicit to satisfy tests */
    constexpr position(const std::pair<std::int32_t, std::int32_t>& pr) noexcept
        : position(pr.first, pr.second)
    {}
};

/* equality helpers so that std::pair<int,int> can be compared with position */
constexpr bool operator==(const std::pair<int, int>& lhs,
                           const position& rhs) noexcept
{
    return (lhs.first == static_cast<std::int32_t>(rhs.row)) &&
           (lhs.second == static_cast<std::int32_t>(rhs.col));
}

constexpr bool operator==(const position& lhs,
                           const std::pair<int, int>& rhs) noexcept
{
    return rhs == lhs;
}

class chess_board final
{
public:
    static constexpr coordinate_t board_size { 8U };

    chess_board() noexcept;                                    // default d1 / d8
    chess_board(position white_pos, position black_pos);

    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] position white() const noexcept;
    [[nodiscard]] position black() const noexcept;

    [[nodiscard]] explicit operator std::string() const;

private:
    position white_pos_ {};
    position black_pos_ {};

    [[nodiscard]] static constexpr bool is_valid_position(position pos) noexcept;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
