#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, std::uint32_t>;

auto frequency(const std::vector<std::string>& texts) -> frequency_map;

}

#endif

