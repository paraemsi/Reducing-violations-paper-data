#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <type_traits>

namespace queen_attack {

using coord_t = std::uint8_t;

struct position {
    coord_t row;
    coord_t column;
};

class chess_board final {
public:
    chess_board() noexcept;
    chess_board(position white, position black);
    template <typename T>
    chess_board(const std::pair<T, T>& white, const std::pair<T, T>& black)
        : chess_board(position{static_cast<coord_t>(white.first), static_cast<coord_t>(white.second)},
                      position{static_cast<coord_t>(black.first), static_cast<coord_t>(black.second)}) {
        static_assert(std::is_integral<T>::value, "Position coordinates must be integral type");
        static_assert(!std::is_same<T, char>::value, "char not permitted for numeric coordinates");
        static_assert(!std::is_same<T, signed char>::value, "signed char not permitted for numeric coordinates");
        static_assert(!std::is_same<T, unsigned char>::value, "unsigned char not permitted for numeric coordinates");
        static_assert(!std::is_same<T, wchar_t>::value, "wchar_t not permitted for numeric coordinates");
        static_assert(!std::is_same<T, char16_t>::value, "char16_t not permitted for numeric coordinates");
        static_assert(!std::is_same<T, char32_t>::value, "char32_t not permitted for numeric coordinates");
        static_assert(!std::is_same<T, bool>::value, "bool not permitted for numeric coordinates");
    }

    position white() const noexcept;
    position black() const noexcept;

    bool can_attack() const noexcept;

    explicit operator std::string() const;

private:
    position white_;
    position black_;
};

template <typename T>
constexpr inline bool operator==(const std::pair<T, T>& lhs, const position& rhs) noexcept {
    const std::int64_t lf = static_cast<std::int64_t>(lhs.first);
    const std::int64_t ls = static_cast<std::int64_t>(lhs.second);
    const std::int64_t rr = static_cast<std::int64_t>(rhs.row);
    const std::int64_t rc = static_cast<std::int64_t>(rhs.column);
    return ((lf == rr) && (ls == rc));
}

template <typename T>
constexpr inline bool operator==(const position& lhs, const std::pair<T, T>& rhs) noexcept {
    return (rhs == lhs);
}

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
