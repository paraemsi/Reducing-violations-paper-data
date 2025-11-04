#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Define fixed-width types to use internally
using coordinate_t = std::int32_t;
using position_t = std::pair<coordinate_t, coordinate_t>;

// The tests use int, so we need to provide that interface
// We'll handle conversions in the implementation
class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    position_t white_pos;
    position_t black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
