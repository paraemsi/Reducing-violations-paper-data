#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H
#include <string>
#include <utility>

namespace queen_attack {

class chess_board {
public:
    explicit chess_board(std::pair<int,int> white = {0, 3},
                         std::pair<int,int> black = {7, 3});

    std::pair<int,int> white() const;
    std::pair<int,int> black() const;

    operator std::string() const;
    bool can_attack() const;

private:
    std::pair<int,int> white_;
    std::pair<int,int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
