#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace parallel_letter_frequency {

using letter_t = char;
using count_t = std::uint32_t;
using frequency_map = std::map<letter_t, count_t>;

frequency_map frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif

