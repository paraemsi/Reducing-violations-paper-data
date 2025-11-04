#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

// Fixed-width type alias for letter counts
using frequency_map = std::unordered_map<char, std::uint32_t>;

// Calculate the total frequency of each (ASCII) letter [a-z] in the input
// texts. Letter matching is case-insensitive and any non-letter character is
// ignored.
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

