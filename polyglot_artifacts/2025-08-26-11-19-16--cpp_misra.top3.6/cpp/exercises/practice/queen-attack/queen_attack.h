#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>

namespace queen_attack {

typedef std::uint8_t board_index_t;

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;

private:
    std::pair<int, int> white_pos;
    std::pair<int, int> black_pos;
};

inline bool operator==(const std::pair<int, int>& lhs, const std::pair<std::uint8_t, std::uint8_t>& rhs)
{
    return (lhs.first == static_cast<int>(rhs.first)) && (lhs.second == static_cast<int>(rhs.second));
}

inline bool operator==(const std::pair<std::uint8_t, std::uint8_t>& lhs, const std::pair<int, int>& rhs)
{
    return (static_cast<int>(lhs.first) == rhs.first) && (static_cast<int>(lhs.second) == rhs.second);
}


}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
