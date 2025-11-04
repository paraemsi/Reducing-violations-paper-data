#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <stdexcept>
#include <utility>
#include <cstdint>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<std::int8_t, std::int8_t> white, std::pair<std::int8_t, std::int8_t> black);
    std::pair<std::int8_t, std::int8_t> white() const;
    std::pair<std::int8_t, std::int8_t> black() const;
    bool can_attack() const;
    
private:
    std::pair<std::int8_t, std::int8_t> white_pos;
    std::pair<std::int8_t, std::int8_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
