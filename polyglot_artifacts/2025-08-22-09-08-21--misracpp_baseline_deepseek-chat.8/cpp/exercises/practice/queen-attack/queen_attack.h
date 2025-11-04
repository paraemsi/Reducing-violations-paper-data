#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int, int> white = std::make_pair(0, 3), 
                std::pair<int, int> black = std::make_pair(7, 3));
    
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    
    bool can_attack() const;
    
private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
