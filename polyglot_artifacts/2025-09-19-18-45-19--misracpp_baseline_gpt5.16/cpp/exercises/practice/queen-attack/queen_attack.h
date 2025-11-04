#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>

namespace queen_attack {

typedef std::pair<int, int> position;

class chess_board {
public:
    chess_board(const position& white, const position& black);
    position white() const;
    position black() const;
    bool can_attack() const;
private:
    position m_white{};
    position m_black{};
};

bool can_attack(const position& white, const position& black);

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
