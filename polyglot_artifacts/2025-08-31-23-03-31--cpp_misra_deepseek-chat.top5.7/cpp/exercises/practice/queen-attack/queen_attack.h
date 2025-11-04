#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Define a type that's not a standard integer type name
using coord_type = std::int8_t;
using internal_position_t = std::pair<coord_type, coord_type>;
using position_t = std::pair<int, int>;

class chess_board {
public:
    chess_board(position_t white, position_t black);
    chess_board();
    explicit chess_board(const std::pair<std::string, std::string>& positions);
    
    position_t white() const;
    position_t black() const;
    bool can_attack() const;
    
private:
    internal_position_t white_queen_;
    internal_position_t black_queen_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
