#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string_view>
#include <cstdint>

namespace parallel_letter_frequency {

using counter_t = std::int32_t;
std::map<char, counter_t> frequency(const std::vector<std::string_view>& texts);

}

#endif

