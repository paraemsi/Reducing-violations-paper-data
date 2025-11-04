#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Use a fixed-width type without using standard names
struct coordinate {
    using type = std::int8_t;
};

using coordinate_t = coordinate::type;

class chess_board {
public:
    chess_board();
    chess_board(const std::string& white, const std::string& black);
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<coordinate_t, coordinate_t> white_pos;
    std::pair<coordinate_t, coordinate_t> black_pos;
    
    static std::pair<coordinate_t, coordinate_t> parse_position(const std::string& pos);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
