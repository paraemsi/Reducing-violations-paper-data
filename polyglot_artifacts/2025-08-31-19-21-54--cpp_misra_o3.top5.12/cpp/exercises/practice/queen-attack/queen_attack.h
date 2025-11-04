#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

namespace queen_attack {

using board_dim_t = std::int32_t;  // 32-bit signed, same underlying type as `int`

class chess_board
{
public:
    using position = std::pair<board_dim_t, board_dim_t>;

    chess_board(
        position white_init = position{ 0, 3 },
        position black_init = position{ 7, 3 }) : white_pos{ white_init }, black_pos{ black_init }
    {
        validate_positions();
    }

    [[nodiscard]] constexpr std::pair<int, int> white() const noexcept
    {
        return { white_pos.first, white_pos.second };
    }

    [[nodiscard]] constexpr std::pair<int, int> black() const noexcept
    {
        return { black_pos.first, black_pos.second };
    }

    [[nodiscard]] bool can_attack() const noexcept
    {
        const std::int32_t row_delta =
            static_cast<std::int32_t>(white_pos.first)
            - static_cast<std::int32_t>(black_pos.first);
        const std::int32_t col_delta =
            static_cast<std::int32_t>(white_pos.second)
            - static_cast<std::int32_t>(black_pos.second);

        const std::int32_t row_abs =
            (row_delta >= 0) ? row_delta : static_cast<std::int32_t>(-row_delta);
        const std::int32_t col_abs =
            (col_delta >= 0) ? col_delta : static_cast<std::int32_t>(-col_delta);

        return (white_pos.first == black_pos.first)           /* same row   */
               || (white_pos.second == black_pos.second)      /* same col   */
               || (row_abs == col_abs);                       /* diagonal   */
    }

    explicit operator std::string() const;

private:
    position white_pos;
    position black_pos;

    void validate_positions() const
    {
        if ((white_pos == black_pos)
            || !is_within_board(white_pos)
            || !is_within_board(black_pos))
        {
            throw std::domain_error("invalid queen position");
        }
    }

    static constexpr bool is_within_board(const position& pos) noexcept
    {
        return (pos.first >= 0) && (pos.first < 8)
               && (pos.second >= 0) && (pos.second < 8);
    }
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
