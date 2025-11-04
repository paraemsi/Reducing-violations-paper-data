#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

struct position {
    std::int32_t first;
    std::int32_t second;
};

template <typename T1, typename T2>
inline bool operator==(const std::pair<T1, T2>& lhs, const position& rhs) noexcept {
    return ((static_cast<std::int32_t>(lhs.first) == rhs.first) && (static_cast<std::int32_t>(lhs.second) == rhs.second));
}

template <typename T1, typename T2>
inline bool operator==(const position& lhs, const std::pair<T1, T2>& rhs) noexcept {
    return ((lhs.first == static_cast<std::int32_t>(rhs.first)) && (lhs.second == static_cast<std::int32_t>(rhs.second)));
}

class chess_board {
public:
    chess_board(position white = position{0, 3},
                position black = position{7, 3});

    position white() const noexcept;
    position black() const noexcept;

    bool can_attack() const noexcept;

private:
    position white_pos_;
    position black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
