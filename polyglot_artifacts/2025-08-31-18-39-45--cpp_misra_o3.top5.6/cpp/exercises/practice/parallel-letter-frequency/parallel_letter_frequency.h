#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

/*
 * Count the occurrences of each alphabetic letter (case–insensitive)
 * across all supplied texts.
 *
 * The function is thread-safe and employs a simple thread-pool model
 * that divides the input range into chunks which are processed in
 * parallel, then merged.
 */
frequency_map frequency(const std::vector<std::string>& texts);
frequency_map frequency(const std::vector<std::string_view>& texts);

} // namespace parallel_letter_frequency

#endif

