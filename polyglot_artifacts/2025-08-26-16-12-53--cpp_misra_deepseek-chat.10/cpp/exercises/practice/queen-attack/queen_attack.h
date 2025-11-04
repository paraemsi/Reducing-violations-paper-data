#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace queen_attack {

// Define a fixed-width type alias using unsigned type to comply with MISRA rules
using coordinate_t = std::uint8_t;
using internal_position_t = std::pair<coordinate_t, coordinate_t>;

// The public interface uses int to match the tests
using position_t = std::pair<int, int>;

class chess_board {
public:
    chess_board();
    chess_board(position_t white, position_t black);
    position_t white() const;
    position_t black() const;
    bool can_attack() const;
    operator std::string() const;
    
private:
    internal_position_t white_pos;
    internal_position_t black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
