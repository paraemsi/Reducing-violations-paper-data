#ifndef QUEEN_ATTACK_H
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <type_traits>

namespace queen_attack {

class chess_board final
{
public:
    using position_t = std::pair<std::uint8_t, std::uint8_t>;

    explicit chess_board(position_t white = position_t{0U, 3U},
                         position_t black = position_t{7U, 3U});

    /*  Generic constructor to accept any integral pair (e.g. std::pair<int,int>)
        Required to interoperate with Exercism test cases that pass `std::pair<int, int>`.
        The static_cast<> operations are intentional and safe because the allowed
        coordinates are restricted to the range 0-7, which fits in std::uint8_t. */
    template<typename T,
             std::enable_if_t<std::is_integral_v<T> &&
                              !std::is_same_v<T, std::uint8_t>, int> = 0>
    explicit chess_board(std::pair<T, T> white,
                         std::pair<T, T> black) :
        chess_board(position_t{static_cast<std::uint8_t>(white.first),
                               static_cast<std::uint8_t>(white.second)},
                    position_t{static_cast<std::uint8_t>(black.first),
                               static_cast<std::uint8_t>(black.second)})
    {
    }

    [[nodiscard]] bool can_attack() const noexcept;
    [[nodiscard]] explicit operator std::string() const;

    /*  Accessors returning coordinates as std::pair<int, int> so that they
        can be compared directly with test data created using std::pair<int,int>. */
    [[nodiscard]] std::pair<int, int> white() const noexcept;
    [[nodiscard]] std::pair<int, int> black() const noexcept;

private:
    position_t m_white;
    position_t m_black;

    static constexpr std::uint8_t board_size{8U};

    static bool positions_equal(position_t lhs, position_t rhs) noexcept;
    static bool on_same_row(position_t lhs, position_t rhs) noexcept;
    static bool on_same_column(position_t lhs, position_t rhs) noexcept;
    static bool on_same_diagonal(position_t lhs, position_t rhs) noexcept;
};

} // namespace queen_attack

#endif // QUEEN_ATTACK_H
