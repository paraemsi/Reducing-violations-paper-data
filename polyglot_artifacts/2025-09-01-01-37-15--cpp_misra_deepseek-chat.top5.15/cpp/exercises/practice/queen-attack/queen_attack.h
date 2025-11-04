#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

class chess_board {
public:
    chess_board();
    chess_board(std::pair<int, int> white, std::pair<int, int> black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    operator std::string() const;
    
private:
    std::pair<std::int32_t, std::int32_t> white_pos;
    std::pair<std::int32_t, std::int32_t> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
