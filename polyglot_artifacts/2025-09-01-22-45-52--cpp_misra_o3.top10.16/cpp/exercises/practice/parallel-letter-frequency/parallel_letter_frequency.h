#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

/*  Alias for the resulting frequency map.
 *  Keys are lowercase letters (‘a’-‘z’), values are their counts.
 */
using letter_t      = char;
using frequency_map = std::unordered_map<letter_t, std::uint32_t>;

/*  Compute the aggregate letter frequencies over all supplied texts.
 *  The counting is case-insensitive and performed in parallel.
 */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif  // PARALLEL_LETTER_FREQUENCY_H

