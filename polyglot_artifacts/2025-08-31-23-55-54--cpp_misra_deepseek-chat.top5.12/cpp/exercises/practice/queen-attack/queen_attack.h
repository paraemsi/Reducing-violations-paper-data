#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

using coordinate_t = std::int16_t;

class chess_board {
public:
    chess_board(const std::string& white, const std::string& black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<coordinate_t, coordinate_t> white_pos;
    std::pair<coordinate_t, coordinate_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
