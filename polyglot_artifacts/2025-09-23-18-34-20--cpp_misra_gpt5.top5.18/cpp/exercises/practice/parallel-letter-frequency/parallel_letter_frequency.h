#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

using char_type = std::string_view::value_type;
using frequency_map = std::unordered_map<char_type, std::uint32_t>;

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;
auto frequency(const std::vector<std::string>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

