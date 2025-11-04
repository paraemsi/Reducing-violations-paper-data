#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Define a type alias that satisfies both MISRA rules and test expectations
using coord_t = int;

class chess_board {
public:
    chess_board();
    chess_board(const std::string& white, const std::string& black);
    std::pair<coord_t, coord_t> white() const;
    std::pair<coord_t, coord_t> black() const;
    bool can_attack() const;
    
private:
    std::pair<coord_t, coord_t> white_pos;
    std::pair<coord_t, coord_t> black_pos;
    
    std::pair<coord_t, coord_t> parse_position(const std::string& pos) const;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
