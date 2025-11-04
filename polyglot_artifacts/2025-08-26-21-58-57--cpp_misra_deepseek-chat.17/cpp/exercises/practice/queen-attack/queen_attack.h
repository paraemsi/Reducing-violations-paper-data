#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<std::int8_t, std::int8_t> white_pos;
    std::pair<std::int8_t, std::int8_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
