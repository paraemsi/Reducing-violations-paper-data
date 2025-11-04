#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Alias for the coordinate type that matches what the tests expect
using coord_t = std::int32_t;

class chess_board {
public:
    chess_board(const std::string& white, const std::string& black);
    std::pair<coord_t, coord_t> white() const;
    std::pair<coord_t, coord_t> black() const;
    bool can_attack() const;
    
private:
    std::pair<coord_t, coord_t> white_position;
    std::pair<coord_t, coord_t> black_position;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
