#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);
    chess_board() : white_(std::make_pair(static_cast<std::int32_t>(0), static_cast<std::int32_t>(3))), 
                    black_(std::make_pair(static_cast<std::int32_t>(7), static_cast<std::int32_t>(3))) {}
    
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    
    bool can_attack() const;
    
    operator std::string() const;
    
private:
    std::pair<std::int32_t, std::int32_t> white_;
    std::pair<std::int32_t, std::int32_t> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
