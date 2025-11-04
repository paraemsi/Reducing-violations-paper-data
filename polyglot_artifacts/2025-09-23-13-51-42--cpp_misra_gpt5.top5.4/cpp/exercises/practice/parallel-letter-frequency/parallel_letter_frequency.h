#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, std::uint32_t>;

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

