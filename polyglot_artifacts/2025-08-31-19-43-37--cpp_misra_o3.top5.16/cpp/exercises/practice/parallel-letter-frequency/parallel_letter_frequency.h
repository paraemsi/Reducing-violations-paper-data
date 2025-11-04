#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*
 * Calculate the frequency of each letter (case-insensitive) that occurs
 * in the supplied collection of texts.
 *
 * The work is split across several asynchronous tasks and the partial
 * results are merged before returning.
 */
[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts)
    -> std::map<char, int>;

}  // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

