#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// MISRA: use fixed-width integer types via an alias for readability.
using count_t = std::uint32_t;
using frequency_map = std::map<char, count_t>;

// Count the frequency of letters (case-insensitive, ASCII/classic locale) across all texts.
// The function employs parallel processing internally.
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

