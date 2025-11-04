#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <stdexcept>
#include <array>

namespace queen_attack {

/*  Board coordinates are 0-indexed, left-to-right (columns) and top-to-bottom
 *  (rows).  Only values in the range [0, 7] are valid for either component.
 */
using board_index = std::uint8_t;

class chess_board {
public:
    /*  Construct a board with explicit white and black queen positions.
     *  Throws std::domain_error if any position is outside the board
     *  or if the queens occupy the same square.
     */
    chess_board(std::pair<board_index, board_index> white_pos,
                std::pair<board_index, board_index> black_pos);

    std::pair<std::int32_t, std::int32_t> white() const noexcept;
    std::pair<std::int32_t, std::int32_t> black() const noexcept;

    /*  Determine whether the two queens can attack each other.            */
    bool can_attack() const noexcept;

    /*  Produce an ASCII representation of the board that matches
     *  the Exercism specification.                                         */
    explicit operator std::string() const;

private:
    std::pair<board_index, board_index> m_white{};
    std::pair<board_index, board_index> m_black{};

    static constexpr board_index board_size{static_cast<board_index>(8U)};
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
