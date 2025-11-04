#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace queen_attack {

// Define a type alias to comply with MISRA rules while matching the test interface
using coordinate_t = std::int32_t;

class chess_board {
public:
    chess_board(std::pair<coordinate_t, coordinate_t> white, std::pair<coordinate_t, coordinate_t> black);
    std::pair<coordinate_t, coordinate_t> white() const;
    std::pair<coordinate_t, coordinate_t> black() const;
    bool can_attack() const;
    
private:
    std::pair<std::int8_t, std::int8_t> white_pos;
    std::pair<std::int8_t, std::int8_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
