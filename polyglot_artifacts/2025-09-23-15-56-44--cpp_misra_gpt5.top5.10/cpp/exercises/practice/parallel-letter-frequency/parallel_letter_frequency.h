#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

 // Type alias for the frequency map: characters to their occurrence counts.
using letter_t = char;
using frequency_map = std::unordered_map<letter_t, std::uint32_t>;

// Compute the frequency of letters (case-insensitive) across a list of texts.
// Only alphabetic characters are counted; everything else is ignored.
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

