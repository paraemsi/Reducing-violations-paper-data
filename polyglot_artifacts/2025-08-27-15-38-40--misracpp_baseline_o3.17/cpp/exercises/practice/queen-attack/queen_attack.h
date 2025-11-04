#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <string>
#include <utility>
#include <stdexcept>

namespace queen_attack {

class chess_board {
 public:
  // row, column – both zero-indexed, 0‥7
  chess_board(std::pair<int, int> white = {0, 3},
              std::pair<int, int> black = {7, 3});

  std::pair<int, int> white() const;
  std::pair<int, int> black() const;

  bool can_attack() const;

  // allow implicit conversion to a printable board
  operator std::string() const;

 private:
  std::pair<int, int> white_;
  std::pair<int, int> black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
