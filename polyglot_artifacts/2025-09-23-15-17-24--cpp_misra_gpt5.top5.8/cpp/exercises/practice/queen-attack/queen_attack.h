#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>
#include <type_traits>

namespace queen_attack {

using coord_t = std::int32_t;
using position = std::pair<coord_t, coord_t>;

// Determine if two queens can attack each other on an 8x8 chessboard.
// Throws std::domain_error if any position is out of range [0,7] or both positions are identical.
bool can_attack(const position& white, const position& black);

// Convenience template overload to accept pairs of any integral (non-char) type.
// This forwards to the fixed-width implementation after safe, explicit conversion.
template <typename T, typename = std::enable_if_t<(std::is_integral<T>::value && (!std::is_same<T, char>::value) && (!std::is_same<T, signed char>::value) && (!std::is_same<T, unsigned char>::value) && (std::is_signed<T>::value == std::is_signed<coord_t>::value) && (sizeof(T) <= sizeof(coord_t)))>>
inline bool can_attack(const std::pair<T, T>& white, const std::pair<T, T>& black)
{
    const position w{static_cast<coord_t>(white.first), static_cast<coord_t>(white.second)};
    const position b{static_cast<coord_t>(black.first), static_cast<coord_t>(black.second)};
    return can_attack(w, b);
}


class chess_board {
public:
    using coord_type = coord_t;
    using position_type = position;

    chess_board(const position& white, const position& black);

    template <typename T, typename = std::enable_if_t<(std::is_integral<T>::value && (!std::is_same<T, char>::value) && (!std::is_same<T, signed char>::value) && (!std::is_same<T, unsigned char>::value) && (std::is_signed<T>::value == std::is_signed<coord_t>::value) && (sizeof(T) <= sizeof(coord_t)))>>
    chess_board(const std::pair<T, T>& white, const std::pair<T, T>& black)
        : chess_board(position{static_cast<coord_t>(white.first), static_cast<coord_t>(white.second)},
                      position{static_cast<coord_t>(black.first), static_cast<coord_t>(black.second)})
    {
    }

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    position white_;
    position black_;
};  // class chess_board

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
