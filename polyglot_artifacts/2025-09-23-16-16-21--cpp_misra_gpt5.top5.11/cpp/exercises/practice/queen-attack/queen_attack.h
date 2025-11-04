#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

// Position as (row, column), zero-indexed [0..7].
using position = std::pair<int, int>;

// Determine if two queens can attack each other given their positions.
bool can_attack(const position& white, const position& black);

// Chess board holding white/black queen positions.
class chess_board {
public:
    // Defaults: white at (0,3), black at (7,3)
    explicit chess_board(
        position white_pos = position{0, 3},
        position black_pos = position{7, 3}
    );

    position white() const;
    position black() const;

    bool can_attack() const;

    // String representation (8x8), rows separated by '\n', cells separated by spaces.
    operator std::string() const;

private:
    position white_;
    position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
