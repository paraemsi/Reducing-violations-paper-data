#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*  Fixed-width unsigned integer type used for all counters
    to comply with MISRA “no plain int” rule. */
using count_t = std::uint32_t;

/*  Compute the letter frequency for a collection of text fragments.
    The algorithm is parallelised; the order of the input texts is irrelevant,
    and the result map holds lower-case letters only. */
auto frequency(const std::vector<std::string>& texts) -> std::unordered_map<char, count_t>;
auto frequency(const std::vector<std::string_view>& texts) -> std::unordered_map<char, count_t>;

} // namespace parallel_letter_frequency

#endif

