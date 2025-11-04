#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

/*  Type alias for the resulting map:
 *  key   : lower-case ASCII letter
 *  value : occurrence count (32-bit unsigned)
 */
using frequency_map = std::unordered_map<char, std::uint32_t>;

/*  Calculate the frequency of the 26 Latin letters (case-insensitive)
 *  appearing in the supplied texts.  Processing is performed in parallel
 *  using a thread pool sized to hardware concurrency.
 */
frequency_map frequency(const std::vector<std::string_view>& texts);

/*  Convenience overload accepting std::string objects                       */
frequency_map frequency(const std::vector<std::string>& texts);

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

