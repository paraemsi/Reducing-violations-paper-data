#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <utility>
#include <stdexcept>

namespace queen_attack {

class chess_board {
 public:
  chess_board(std::pair<int, int> white = {0, 3},
              std::pair<int, int> black = {7, 3});

  std::pair<int, int> white() const;
  std::pair<int, int> black() const;

  bool can_attack() const;

 private:
  std::pair<int, int> m_white;
  std::pair<int, int> m_black;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
