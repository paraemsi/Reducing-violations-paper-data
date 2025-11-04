#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <locale>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*
 * Map type holding the counts for each letter.
 * A fixed-width unsigned integer is used to satisfy the MISRA rule
 * forbidding plain 'int'.
 *
 * The Exercism test-suite expects the alias name `frequency_map`.
 * We keep an internal synonym `letter_counts_map_t` to avoid
 * touching the implementation code.
 */
using frequency_map       = std::map<char, std::uint32_t>;
using letter_counts_map_t = frequency_map;  // internal synonym kept for compatibility

/*
 * Compute the overall letter frequency for a list of texts.
 * The work is distributed across multiple asynchronous tasks.
 */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif  // PARALLEL_LETTER_FREQUENCY_H

