#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

auto frequency(const std::vector<std::string>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

