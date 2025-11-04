#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace queen_attack {

struct position final {
    std::uint8_t row;
    std::uint8_t column;
};

constexpr inline bool operator==(const position& lhs, const position& rhs) noexcept
{
    return ((lhs.row == rhs.row) && (lhs.column == rhs.column));
}

constexpr inline bool operator!=(const position& lhs, const position& rhs) noexcept
{
    return ((lhs.row != rhs.row) || (lhs.column != rhs.column));
}

template <typename T1, typename T2>
constexpr inline bool operator==(const std::pair<T1, T2>& lhs, const position& rhs) noexcept
{
    return ((static_cast<std::int32_t>(lhs.first) == rhs.row) && (static_cast<std::int32_t>(lhs.second) == rhs.column));
}

class chess_board final {
public:
    chess_board() noexcept;
    chess_board(position white, position black);
    position white() const noexcept;
    position black() const noexcept;
    bool can_attack() const noexcept;

    template <typename T1, typename T2>
    chess_board(std::pair<T1, T2> white, std::pair<T1, T2> black);

private:
    template <typename T1, typename T2>
    static position make_position(std::pair<T1, T2> p);

    static constexpr bool in_bounds(std::int32_t v) noexcept
    {
        return ((v >= 0) && (v < 8));
    }

    position white_;
    position black_;
};

template <typename T1, typename T2>
inline position chess_board::make_position(std::pair<T1, T2> p)
{
    static_assert(std::is_integral_v<T1>, "row must be integral");
    static_assert(std::is_integral_v<T2>, "column must be integral");
    return position{static_cast<std::int32_t>(p.first), static_cast<std::int32_t>(p.second)};
}

template <typename T1, typename T2>
inline chess_board::chess_board(std::pair<T1, T2> white, std::pair<T1, T2> black)
    : chess_board(chess_board::make_position(white), chess_board::make_position(black))
{
}

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
