#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    struct position {
        std::uint8_t row{};
        std::uint8_t column{};

        position() = default;

        position(std::uint8_t r, std::uint8_t c) noexcept : row{r}, column{c} {}

        /* Accept the test-suite’s std::pair<int,int> without leaking
         * non-MISRA types through the public API. */
        explicit position(const std::pair<int, int>& p) noexcept
            : row{static_cast<std::uint8_t>(p.first)},
              column{static_cast<std::uint8_t>(p.second)} {}

        /* Allow implicit comparison with std::pair<int,int>. */
        operator std::pair<int, int>() const noexcept
        {
            return {static_cast<int>(row), static_cast<int>(column)};
        }

        [[nodiscard]] bool operator==(const position& other) const noexcept
        {
            return ((row == other.row) && (column == other.column));
        }

        /* Enable direct comparison between a test-suite std::pair<int,int>
         * and a position object, regardless of operand order. */
        [[nodiscard]] friend bool operator==(const std::pair<int, int>& lhs,
                                             const position& rhs) noexcept
        {
            return ((lhs.first == static_cast<int>(rhs.row)) &&
                    (lhs.second == static_cast<int>(rhs.column)));
        }

        [[nodiscard]] friend bool operator==(const position& lhs,
                                             const std::pair<int, int>& rhs) noexcept
        {
            return (rhs == lhs);
        }

        /* Inequality operators required by some tests */
        [[nodiscard]] friend bool operator!=(const std::pair<int, int>& lhs,
                                             const position& rhs) noexcept
        {
            return !(lhs == rhs);
        }

        [[nodiscard]] friend bool operator!=(const position& lhs,
                                             const std::pair<int, int>& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };

    /* Board is always 8×8 squares. Made public so helper functions
     * outside the class can use it without violating access rules. */
    static constexpr std::uint8_t board_size{8U};

    chess_board() noexcept;
    chess_board(const position& white_pos, const position& black_pos);
    chess_board(const std::pair<int, int>& white_pos, const std::pair<int, int>& black_pos);

    [[nodiscard]] position white() const noexcept;
    [[nodiscard]] position black() const noexcept;

    [[nodiscard]] bool can_attack() const noexcept;

    [[nodiscard]] std::string board() const;
    [[nodiscard]] operator std::string() const { return board(); }

private:

    position m_white{};
    position m_black{};

    static void validate_position(const position& pos);
};
}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
