#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <string_view>
#include <cstdint>

namespace parallel_letter_frequency {

/* fixed-width counter type that satisfies MISRA rule set */
using count_type = std::uint32_t;

/* public alias used by the tests */
using frequency_map = std::unordered_map<char, count_type>;

/* Calculate the frequency of each ASCII letter (case-insensitive) in
 * the supplied collection of texts.  The function is thread-safe and
 * employs parallel execution internally. */
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

