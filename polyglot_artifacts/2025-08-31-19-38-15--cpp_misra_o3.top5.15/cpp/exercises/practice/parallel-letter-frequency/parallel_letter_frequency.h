#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <cstddef>           // for std::size_t
#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace parallel_letter_frequency {

//  Type alias for the result map – avoids repeating the verbose type
using frequency_map = std::map<char, std::uint32_t>;

/*
 * Calculate the letter frequency for a collection of text fragments.
 *
 * The operation is carried out in parallel – the input range is split
 * into chunks that are processed by multiple worker threads and the
 * partial results are merged before returning.
 */
auto frequency(const std::vector<std::string>& texts) -> frequency_map;
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

