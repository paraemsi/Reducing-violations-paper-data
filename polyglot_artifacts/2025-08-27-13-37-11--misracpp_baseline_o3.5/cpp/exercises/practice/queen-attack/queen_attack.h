#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int,int> white_position = {0, 3},
                std::pair<int,int> black_position = {7, 3});

    std::pair<int,int> white() const;
    std::pair<int,int> black() const;

    bool can_attack() const;

    operator std::string() const;

private:
    std::pair<int,int> white_pos_;
    std::pair<int,int> black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
