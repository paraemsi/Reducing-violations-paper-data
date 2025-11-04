#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <string>
#include <ostream>

namespace queen_attack {

class chess_board {
public:
    // Each position is {row, column} with 0 ≤ row,col < 8
    chess_board(std::pair<int,int> white = {0, 3},
                std::pair<int,int> black = {7, 3});

    std::pair<int,int> white() const noexcept;
    std::pair<int,int> black() const noexcept;
    bool can_attack() const noexcept;

    explicit operator std::string() const;

    // Enable streaming a chess_board directly to an output stream.
    friend std::ostream& operator<<(std::ostream& os,
                                    const chess_board& board);

private:
    std::pair<int,int> white_pos_;
    std::pair<int,int> black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
