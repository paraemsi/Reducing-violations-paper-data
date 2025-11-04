#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/**
 * Calculate the letter frequency over the supplied texts using all available
 * hardware threads.
 */
frequency_map frequency(const std::vector<std::string_view>& input);

/**
 * Calculate the letter frequency over the supplied texts using `workers`
 * parallel worker threads.
 */
frequency_map frequency(const std::vector<std::string_view>& input, std::size_t workers);

} // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

