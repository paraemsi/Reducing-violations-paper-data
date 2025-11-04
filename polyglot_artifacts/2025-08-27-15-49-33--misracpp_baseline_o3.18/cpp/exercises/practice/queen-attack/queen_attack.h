#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int,int> white = {0, 3}, std::pair<int,int> black = {7, 3});
    std::pair<int,int> white() const noexcept;
    std::pair<int,int> black() const noexcept;
    bool can_attack() const noexcept;
    operator std::string() const;

private:
    std::pair<int,int> white_pos_;
    std::pair<int,int> black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
