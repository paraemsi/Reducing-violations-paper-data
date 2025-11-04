#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

using letter_frequency_map = std::map<char, std::uint32_t>;

letter_frequency_map frequency(const std::vector<std::string>& texts);

} // namespace parallel_letter_frequency

#endif

