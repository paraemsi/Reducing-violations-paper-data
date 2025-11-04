#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <string>
#include <utility>
#include <type_traits>

namespace queen_attack {

using board_index_t = std::uint8_t;
using coordinate_t = std::pair<board_index_t, board_index_t>;

class chess_board final {
public:
    chess_board() noexcept;
    chess_board(coordinate_t white_pos, coordinate_t black_pos);

    /* Accept positions supplied as any integral pair (e.g. std::pair<int, int>)
       to remain compatible with existing client code while internally
       converting to the fixed-width coordinate_t type required by MISRA rules. */
    template <typename T,
              typename = typename std::enable_if<(std::is_integral<T>::value && !std::is_same<T, board_index_t>::value)>::type>
    chess_board(std::pair<T, T> white_pos, std::pair<T, T> black_pos)
        : chess_board(
              coordinate_t{static_cast<board_index_t>(white_pos.first),
                           static_cast<board_index_t>(white_pos.second)},
              coordinate_t{static_cast<board_index_t>(black_pos.first),
                           static_cast<board_index_t>(black_pos.second)}) {}

    std::pair<int, int> white() const noexcept;
    std::pair<int, int> black() const noexcept;
    bool can_attack() const noexcept;
    std::string to_string() const;
    operator std::string() const { return to_string(); }

private:
    coordinate_t white_position_;
    coordinate_t black_position_;
};

} // namespace queen_attack

#endif // QUEEN_ATTACK_H
