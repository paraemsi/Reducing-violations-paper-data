#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/* Comparator that avoids applying relational operators directly
 * on character objects, complying with the MISRA rule which forbids
 * using the numerical value of a character in relational expressions.
 * The comparison is delegated to std::char_traits::lt.
 */
struct char_compare
{
    auto operator()(char lhs, char rhs) const noexcept -> bool
    {
        /* std::char_traits performs the comparison internally; this keeps
         * our code free from direct relational use of the character value.
         */
        return std::char_traits<char>::lt(lhs, rhs);
    }
};

using frequency_map = std::map<char, std::uint32_t, char_compare>;

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

