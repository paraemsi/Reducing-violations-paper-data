#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int,int> white = {0,3},
                std::pair<int,int> black = {7,3});

    std::pair<int,int> white() const;
    std::pair<int,int> black() const;

    bool can_attack() const;

    std::string to_string() const;

private:
    static bool is_valid(const std::pair<int,int>& pos);
    static constexpr int kBoardSize = 8;

    std::pair<int,int> white_pos_;
    std::pair<int,int> black_pos_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
