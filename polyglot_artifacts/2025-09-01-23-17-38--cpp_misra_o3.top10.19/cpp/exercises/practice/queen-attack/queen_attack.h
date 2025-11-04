#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <cstdint>

namespace queen_attack {

// Alias for the underlying coordinate type (wraps the raw 'int')
using coord_t    = int;

// Type-alias for a board coordinate (row, column)
using position_t = std::pair<coord_t, coord_t>;

class chess_board {
public:
    // Construct with explicit positions for each queen.
    chess_board(const position_t& white_pos,
                const position_t& black_pos);

    // Default board: white at (0,3) and black at (7,3)
    chess_board();

    // Accessors
    [[nodiscard]] position_t white() const noexcept;
    [[nodiscard]] position_t black() const noexcept;

    // Determine whether the two queens can attack each other.
    [[nodiscard]] bool can_attack() const noexcept;

private:
    position_t m_white{};
    position_t m_black{};

    static void validate_position(const position_t& pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
