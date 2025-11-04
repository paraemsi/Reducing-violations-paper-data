#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

/*  Count the frequency of each ASCII letter [a-z] (case–insensitive)
    appearing in the supplied texts.
*/
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif  // PARALLEL_LETTER_FREQUENCY_H

