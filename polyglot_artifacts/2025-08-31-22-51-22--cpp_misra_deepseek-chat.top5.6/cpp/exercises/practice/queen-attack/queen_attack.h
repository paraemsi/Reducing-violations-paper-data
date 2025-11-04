#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace queen_attack {

// Use a struct to wrap the fixed-width type
struct chess_coordinate {
    using type = std::uint_fast8_t;
};

using coordinate_t = chess_coordinate::type;

class chess_board {
public:
    chess_board(std::pair<coordinate_t, coordinate_t> white, std::pair<coordinate_t, coordinate_t> black);
    explicit chess_board(const std::pair<std::string, std::string>& positions);
    
    std::pair<int, int> white() const;
    std::pair<int, int> black() const;
    bool can_attack() const;
    
private:
    std::pair<coordinate_t, coordinate_t> white_;
    std::pair<coordinate_t, coordinate_t> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
