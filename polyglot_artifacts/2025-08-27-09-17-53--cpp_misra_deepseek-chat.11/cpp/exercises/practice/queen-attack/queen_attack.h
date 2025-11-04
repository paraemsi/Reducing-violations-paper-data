#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <cstdint>

namespace queen_attack {

// Define a coordinate type that can be used to satisfy both MISRA rules and test expectations
using coord_t = std::int8_t;
using position_t = std::pair<coord_t, coord_t>;

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);
    chess_board(const std::string& white, const std::string& black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    position_t white_pos;
    position_t black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
