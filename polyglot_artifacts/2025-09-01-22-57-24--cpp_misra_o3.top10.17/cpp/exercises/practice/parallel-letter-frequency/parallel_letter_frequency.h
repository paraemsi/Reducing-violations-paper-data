#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> std::unordered_map<char, std::uint32_t>;

}

#endif

