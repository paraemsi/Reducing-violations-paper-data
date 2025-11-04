#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

using letter_frequency_map = std::map<char, std::uint32_t>;

auto frequency(const std::vector<std::string>& texts) -> letter_frequency_map;

}

#endif

