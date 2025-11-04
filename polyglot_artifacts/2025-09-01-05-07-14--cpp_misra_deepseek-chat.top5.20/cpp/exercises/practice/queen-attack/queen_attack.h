#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <cstdint>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::string& white, const std::string& black);
    bool can_attack() const;
    
    // Add getters to access queen positions if needed
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    
private:
    std::pair<std::int8_t, std::int8_t> white_;
    std::pair<std::int8_t, std::int8_t> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
