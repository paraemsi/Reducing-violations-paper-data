#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

struct position final {
    using value_type = std::uint8_t;

    value_type row{static_cast<value_type>(0U)};
    value_type column{static_cast<value_type>(0U)};

    constexpr position() = default;

    constexpr position(value_type r, value_type c) noexcept
        : row(r), column(c)
    {
    }


};

template <typename T, typename U>
constexpr bool operator==(const std::pair<T, U>& lhs, const position& rhs) noexcept
{
    return ((static_cast<position::value_type>(lhs.first) == rhs.row) &&
            (static_cast<position::value_type>(lhs.second) == rhs.column));
}

template <typename T, typename U>
constexpr bool operator==(const position& lhs, const std::pair<T, U>& rhs) noexcept
{
    return ((lhs.row == static_cast<position::value_type>(rhs.first)) &&
            (lhs.column == static_cast<position::value_type>(rhs.second)));
}

class chess_board final {
public:
    static constexpr position::value_type board_size = static_cast<position::value_type>(8U);

    chess_board(position white = position{static_cast<position::value_type>(0U), static_cast<position::value_type>(3U)},
                position black = position{static_cast<position::value_type>(7U), static_cast<position::value_type>(3U)});

    template <typename T1, typename U1, typename T2, typename U2>
    chess_board(const std::pair<T1, U1>& w, const std::pair<T2, U2>& b)
        : chess_board(position{static_cast<position::value_type>(w.first), static_cast<position::value_type>(w.second)},
                      position{static_cast<position::value_type>(b.first), static_cast<position::value_type>(b.second)})
    {
    }

    position white() const;
    position black() const;
    bool can_attack() const;
    explicit operator std::string() const;

private:
    position white_;
    position black_;
    static void validate(position pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
