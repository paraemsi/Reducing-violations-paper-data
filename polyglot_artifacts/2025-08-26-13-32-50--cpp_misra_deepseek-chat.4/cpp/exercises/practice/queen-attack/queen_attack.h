#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<std::int32_t, std::int32_t> white, std::pair<std::int32_t, std::int32_t> black);
    std::pair<std::int32_t, std::int32_t> white() const;
    std::pair<std::int32_t, std::int32_t> black() const;
    bool can_attack() const;
    
private:
    std::pair<std::int32_t, std::int32_t> white_position;
    std::pair<std::int32_t, std::int32_t> black_position;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
