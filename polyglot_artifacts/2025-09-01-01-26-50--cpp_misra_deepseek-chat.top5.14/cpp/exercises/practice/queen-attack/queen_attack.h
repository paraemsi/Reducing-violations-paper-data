#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <stdexcept>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(const std::string& white, const std::string& black);
    explicit chess_board() : chess_board("a1", "a2") {}
    
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
