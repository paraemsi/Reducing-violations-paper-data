#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace parallel_letter_frequency {

/*
 * Count the frequency of letters (case-insensitive) in a collection of texts.
 * The algorithm may run tasks in parallel to improve throughput.
 *
 * The returned map contains only those letters that occur at least once.
 */
auto frequency(const std::vector<std::string_view>& texts) -> std::map<char, std::uint32_t>;

} // namespace parallel_letter_frequency

#endif

