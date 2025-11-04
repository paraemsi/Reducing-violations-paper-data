#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace queen_attack {

// To comply with MISRA, we'll use a fixed-width type internally
using coord_t = std::int8_t;
// The interface must match the tests, which use int
using position_t = std::pair<int, int>;

class chess_board {
public:
    chess_board();
    chess_board(position_t white, position_t black);
    position_t white() const;
    position_t black() const;
    bool can_attack() const;
    
private:
    // Use fixed-width types internally
    std::pair<coord_t, coord_t> white_pos;
    std::pair<coord_t, coord_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
