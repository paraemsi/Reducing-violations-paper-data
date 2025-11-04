#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*
 * Frequency map: counts per character (letters only).
 * The key is a character; it is not treated as a numeric value.
 * The mapped type uses a fixed-width unsigned integer per the project's MISRA-like rules.
 */
using frequency_map = std::map<char, std::uint32_t>;

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

