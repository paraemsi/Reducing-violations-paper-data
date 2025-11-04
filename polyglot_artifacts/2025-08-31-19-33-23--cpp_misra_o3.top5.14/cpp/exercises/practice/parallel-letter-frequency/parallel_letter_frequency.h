#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

using count_map = std::unordered_map<char, std::uint32_t>;

/*
 * Count the frequency of ASCII letters in the supplied texts.
 * The operation is executed in parallel; the order of processing
 * is unspecified.
 */
count_map frequency(const std::vector<std::string_view>& texts);

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

