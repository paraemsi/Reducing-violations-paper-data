#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

#include <cstdint>
#include <utility>
#include <type_traits>
#include <stdexcept>

namespace queen_attack {

struct position final {
    using coord_t = std::int32_t;

    coord_t row;
    coord_t column;

};

template <typename TFirst, typename TSecond,
          typename = typename std::enable_if<(std::is_integral<TFirst>::value && std::is_integral<TSecond>::value)>::type>
constexpr bool operator==(const std::pair<TFirst, TSecond>& lhs, const position& rhs) noexcept
{
    using signed_t = std::int32_t;
    const signed_t lr = static_cast<signed_t>(lhs.first);
    const signed_t lc = static_cast<signed_t>(lhs.second);
    return ((lr == static_cast<signed_t>(rhs.row)) && (lc == static_cast<signed_t>(rhs.column)));
}

template <typename TFirst, typename TSecond,
          typename = typename std::enable_if<(std::is_integral<TFirst>::value && std::is_integral<TSecond>::value)>::type>
constexpr bool operator==(const position& lhs, const std::pair<TFirst, TSecond>& rhs) noexcept
{
    return (rhs == lhs);
}

class chess_board final {
public:
    chess_board(
        position white = position{
            static_cast<position::coord_t>(0U),
            static_cast<position::coord_t>(3U)},
        position black = position{
            static_cast<position::coord_t>(7U),
            static_cast<position::coord_t>(3U)}) noexcept;

    template <typename TFirst, typename TSecond,
              typename = typename std::enable_if<(std::is_integral<TFirst>::value && std::is_integral<TSecond>::value)>::type>
    explicit chess_board(const std::pair<TFirst, TSecond>& white_pair,
                         const std::pair<TFirst, TSecond>& black_pair)
    {
        using signed_t = std::int32_t;

        const signed_t wr = static_cast<signed_t>(white_pair.first);
        const signed_t wc = static_cast<signed_t>(white_pair.second);
        const signed_t br = static_cast<signed_t>(black_pair.first);
        const signed_t bc = static_cast<signed_t>(black_pair.second);

        const bool white_row_ok = ((wr >= static_cast<signed_t>(0)) && (wr <= static_cast<signed_t>(7)));
        const bool white_col_ok = ((wc >= static_cast<signed_t>(0)) && (wc <= static_cast<signed_t>(7)));
        const bool black_row_ok = ((br >= static_cast<signed_t>(0)) && (br <= static_cast<signed_t>(7)));
        const bool black_col_ok = ((bc >= static_cast<signed_t>(0)) && (bc <= static_cast<signed_t>(7)));

        if (((!white_row_ok) || (!white_col_ok)) || ((!black_row_ok) || (!black_col_ok))) {
            throw std::domain_error("position out of bounds");
        }

        const position w{
            static_cast<position::coord_t>(wr),
            static_cast<position::coord_t>(wc)};
        const position b{
            static_cast<position::coord_t>(br),
            static_cast<position::coord_t>(bc)};

        if ((w.row == b.row) && (w.column == b.column)) {
            throw std::domain_error("positions must be distinct");
        }

        white_ = w;
        black_ = b;
    }

    position white() const noexcept;
    position black() const noexcept;

    bool can_attack() const noexcept;

private:
    position white_;
    position black_;
};

}  // namespace queen_attack

#endif // QUEEN_ATTACK_H
