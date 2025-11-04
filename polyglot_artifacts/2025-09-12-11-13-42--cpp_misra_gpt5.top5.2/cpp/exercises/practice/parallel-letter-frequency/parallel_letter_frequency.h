#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Alias to represent the frequency map of letters.
// Note: Using std::map<char, std::uint32_t> for counts to comply with MISRA rules.
using frequency_map = std::map<char, std::uint32_t>;

// Compute the frequency of letters (case-insensitive) across multiple texts,
// employing parallel computation where beneficial.
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

