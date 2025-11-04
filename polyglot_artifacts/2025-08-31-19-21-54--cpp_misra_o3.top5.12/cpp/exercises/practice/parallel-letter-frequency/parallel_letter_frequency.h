#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

