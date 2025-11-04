#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Alias to satisfy MISRA rule about not using standard integer types directly
using coord_t = std::int32_t;

class chess_board {
public:
    chess_board(std::pair<coord_t, coord_t> white, std::pair<coord_t, coord_t> black);
    std::pair<coord_t, coord_t> white() const;
    std::pair<coord_t, coord_t> black() const;
    bool can_attack() const;
    
private:
    std::pair<coord_t, coord_t> white_pos;
    std::pair<coord_t, coord_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
