#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

using board_index_t = std::int32_t;
using position      = std::pair<board_index_t, board_index_t>;

class chess_board
{
public:
    chess_board(const position& white_pos = position{0, 3},
                const position& black_pos = position{7, 3});

    [[nodiscard]] position white() const noexcept;
    [[nodiscard]] position black() const noexcept;
    [[nodiscard]] bool can_attack() const noexcept;

    explicit operator std::string() const;

private:
    position white_coord_;
    position black_coord_;

    [[nodiscard]] static bool is_on_board(const position& pos) noexcept;
};

/* -------------------------------------------------------------------------- */
/*  Equality helpers to compare with std::pair<int,int> used by the tests     */
/* -------------------------------------------------------------------------- */
[[nodiscard]] inline bool operator==(const position& lhs,
                                     const std::pair<int, int>& rhs) noexcept
{
    /* Explicit casts keep numeric categories and signedness aligned. */
    return (lhs.first == static_cast<board_index_t>(rhs.first)) &&
           (lhs.second == static_cast<board_index_t>(rhs.second));
}

[[nodiscard]] inline bool operator==(const std::pair<int, int>& lhs,
                                     const position& rhs) noexcept
{
    return rhs == lhs;
}

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
