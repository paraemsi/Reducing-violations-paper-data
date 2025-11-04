#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

 // Map of letter -> frequency count
using frequency_map = std::unordered_map<char, std::uint32_t>;

// Compute letter frequency (case-insensitive, a-z only) across all texts in parallel
auto frequency(const std::vector<std::string>& texts) -> frequency_map;
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

