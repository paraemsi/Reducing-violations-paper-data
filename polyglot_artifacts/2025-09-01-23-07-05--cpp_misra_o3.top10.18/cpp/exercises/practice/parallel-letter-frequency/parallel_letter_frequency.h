#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string_view>
#include <unordered_map>
#include <cstdint>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

/*
 * Calculate the letter frequency for a collection of texts.
 * The algorithm runs each text in a separate thread and
 * combines the partial results.
 */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

} // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

