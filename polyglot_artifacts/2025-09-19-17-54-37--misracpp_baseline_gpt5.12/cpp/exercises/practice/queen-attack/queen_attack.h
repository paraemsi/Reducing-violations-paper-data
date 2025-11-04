#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>

namespace queen_attack {

using position = std::pair<int, int>;

class chess_board {
public:
    chess_board(position white = {0, 3}, position black = {7, 3});
    position white() const;
    position black() const;
    bool can_attack() const;
    explicit operator std::string() const;

private:
    position white_;
    position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
