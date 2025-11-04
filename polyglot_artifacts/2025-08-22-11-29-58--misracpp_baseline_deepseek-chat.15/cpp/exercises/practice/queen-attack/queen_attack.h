#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>
#include <string>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int, int> white = std::make_pair(0, 0), 
                std::pair<int, int> black = std::make_pair(7, 7));
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<int, int> white_pos;
    std::pair<int, int> black_pos;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
