#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <stdexcept>
#include <utility>
#include <cstdint>

namespace queen_attack {

// Define a type alias for coordinate values
using coord_t = std::int8_t;

class chess_board {
public:
    chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black);
    explicit chess_board() : white_(std::make_pair(static_cast<coord_t>(0), static_cast<coord_t>(3))), 
                            black_(std::make_pair(static_cast<coord_t>(7), static_cast<coord_t>(3))) {}
    
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    
    bool can_attack() const;
    
private:
    std::pair<coord_t, coord_t> white_;
    std::pair<coord_t, coord_t> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
