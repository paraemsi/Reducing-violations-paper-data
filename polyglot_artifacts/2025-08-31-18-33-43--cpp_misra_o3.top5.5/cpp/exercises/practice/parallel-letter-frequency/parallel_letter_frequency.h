#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map_t = std::unordered_map<char, std::uint32_t>;

/* Calculate the frequency of each ASCII letter (case-insensitive) across
   all input texts. Processing of individual texts is performed in parallel. */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map_t;

}

#endif

