#ifndef QUEEN_ATTACK_H
#define QUEEN_ATTACK_H
#include <cstdint>
#include <string>
#include <utility>

namespace queen_attack {

struct coordinate {
    std::uint8_t first{static_cast<std::uint8_t>(0U)};
    std::uint8_t second{static_cast<std::uint8_t>(0U)};

    coordinate() = default;

    coordinate(std::uint8_t col, std::uint8_t row) noexcept
        : first{col}, second{row}
    {
    }

    // Construct from the test-provided std::pair<int,int>
    coordinate(const std::pair<int, int>& p) noexcept
        : first{static_cast<std::uint8_t>(p.first)},
          second{static_cast<std::uint8_t>(p.second)}
    {
    }


    // Defaulted equality – needed internally and for tests
    bool operator==(const coordinate& other) const noexcept = default;
};

// Provide equality between test std::pair<int,int> and our coordinate type.
inline bool operator==(const std::pair<int, int>& lhs,
                       const coordinate&              rhs) noexcept
{
    return ((lhs.first == static_cast<int>(rhs.first)) &&
            (lhs.second == static_cast<int>(rhs.second)));
}

inline bool operator==(const coordinate&              lhs,
                       const std::pair<int, int>& rhs) noexcept
{
    return rhs == lhs;
}

class chess_board {
public:
    chess_board() = default;
    chess_board(coordinate white_pos, coordinate black_pos);

    coordinate white() const noexcept;
    coordinate black() const noexcept;

    bool can_attack() const noexcept;

    explicit operator std::string() const;

private:
    coordinate white_pos_{static_cast<std::uint8_t>(0U), static_cast<std::uint8_t>(3U)};
    coordinate black_pos_{static_cast<std::uint8_t>(7U), static_cast<std::uint8_t>(3U)};
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
