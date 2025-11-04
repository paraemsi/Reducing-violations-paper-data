#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Fixed-width count type to comply with MISRA guidance
using count_t = std::uint32_t;

// Result mapping from character to its frequency
using result_map = std::map<char, count_t>;

// Compute the frequency of letters (A-Z, a-z treated case-insensitively) across all input texts.
// Processing is performed in parallel where possible.
result_map frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif

