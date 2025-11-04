#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace parallel_letter_frequency {

using letter_frequency_map = std::map<char, std::uint32_t>;

/*
 * Calculate the frequency of the alphabetic characters (case-insensitive)
 * appearing in the supplied collection of texts.
 *
 * The function may run the work in parallel; the returned map contains
 * only lowercase ASCII keys 'a' .. 'z' for which at least one occurrence
 * was found.
 */
letter_frequency_map frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif

