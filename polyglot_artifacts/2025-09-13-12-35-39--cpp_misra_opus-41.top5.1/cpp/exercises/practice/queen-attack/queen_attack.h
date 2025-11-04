#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>
#include <stdexcept>

namespace queen_attack {

class queen {
public:
    // Constructor taking position as (row, column)
    queen(std::int32_t row = 0, std::int32_t column = 0);
    
    // Alternative constructor taking a pair
    queen(std::pair<std::int32_t, std::int32_t> position);
    
    // Get position as a pair
    std::pair<std::int32_t, std::int32_t> position() const;
    
    // Equality operator
    bool operator==(const queen& other) const;

private:
    std::int32_t row_;
    std::int32_t column_;
    
    friend class chess_board;
};

class chess_board {
public:
    // Constructor taking two queens
    chess_board(const queen& white_queen, const queen& black_queen);
    
    // Get white queen
    const queen& white() const;
    
    // Get black queen
    const queen& black() const;
    
    // Check if queens can attack each other
    bool can_attack() const;

private:
    queen white_queen_;
    queen black_queen_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
