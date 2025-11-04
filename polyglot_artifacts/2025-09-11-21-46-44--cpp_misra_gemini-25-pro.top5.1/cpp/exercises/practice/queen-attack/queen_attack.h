#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace queen_attack {

using position_t = std::pair<std::int32_t, std::int32_t>;

class chess_board {
   public:
    chess_board(const position_t& white,
                const position_t& black);

    const position_t& white() const;
    const position_t& black() const;
    bool can_attack() const;

    static constexpr std::size_t col_idx{0};
    static constexpr std::size_t row_idx{1};

   private:
    position_t white_;
    position_t black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
