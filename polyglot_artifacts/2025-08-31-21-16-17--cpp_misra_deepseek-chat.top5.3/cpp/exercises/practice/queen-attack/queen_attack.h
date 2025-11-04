#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Define a type alias for the coordinate type
using coord_t = std::int8_t;

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<coord_t, coord_t> white_pos;
    std::pair<coord_t, coord_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
