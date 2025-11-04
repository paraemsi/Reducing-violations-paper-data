#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*  Frequency map alias:
 *  - keys   : letters 'a' .. 'z' (lower-case)
 *  - values : occurrence counter for each letter
 */
using frequency_map = std::unordered_map<char, std::uint32_t>;

/*  Calculate the letter frequency of the supplied texts.
 *  The function is thread-safe and utilises a thread pool that scales
 *  with std::thread::hardware_concurrency().
 */
frequency_map frequency(const std::vector<std::string>& texts);
frequency_map frequency(const std::vector<std::string_view>& texts);

} // namespace parallel_letter_frequency

#endif

