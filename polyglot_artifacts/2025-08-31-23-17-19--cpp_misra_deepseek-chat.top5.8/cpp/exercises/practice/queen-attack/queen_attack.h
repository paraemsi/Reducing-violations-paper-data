#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

using coordinate_t = std::uint8_t;
using position_t = std::pair<coordinate_t, coordinate_t>;

class chess_board {
public:
    chess_board(position_t white, position_t black);
    explicit chess_board(const std::pair<std::string, std::string>& positions);
    
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    position_t white_pos;
    position_t black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
