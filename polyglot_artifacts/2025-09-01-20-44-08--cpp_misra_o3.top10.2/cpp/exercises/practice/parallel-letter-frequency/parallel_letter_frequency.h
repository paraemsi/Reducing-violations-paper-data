#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

/*  Type alias for the resulting container.
 *  Keys are lower-case ASCII letters – values are their respective counts.
 */
using frequency_map = std::unordered_map<char, std::uint32_t>;

/*  Calculate the frequency of every letter (a–z, case-insensitive)
 *  appearing in the supplied collection of texts.
 *  The work is performed in parallel using a pool of std::threads.
 */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

/*  Convenience overload for test-suites that still pass std::string
 *  objects.  It converts each string to a string_view and forwards
 *  to the main implementation to avoid code duplication.
 */
auto frequency(const std::vector<std::string>& texts) -> frequency_map;

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

