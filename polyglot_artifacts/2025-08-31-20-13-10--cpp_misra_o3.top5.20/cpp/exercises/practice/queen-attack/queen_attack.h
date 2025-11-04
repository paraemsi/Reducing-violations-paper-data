#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

class chess_board {
public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black);

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;

    bool can_attack() const;

private:
    std::pair<int, int> white_;
    std::pair<int, int> black_;

    static bool is_valid_position(const std::pair<int, int>& position);
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
