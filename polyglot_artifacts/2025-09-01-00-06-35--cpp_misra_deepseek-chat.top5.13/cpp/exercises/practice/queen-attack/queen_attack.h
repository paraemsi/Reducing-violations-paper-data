#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

// Use int to match the test cases
using position_t = std::pair<int, int>;

class chess_board {
public:
    chess_board(position_t white, position_t black);
    position_t white() const;
    position_t black() const;
    bool can_attack() const;
    
private:
    position_t white_pos;
    position_t black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
