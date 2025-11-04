#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>
#include <string_view>
#include <cstdint>

namespace parallel_letter_frequency {

using counter_t = int;   // Alias keeps MISRA rule while matching test expectations

auto frequency(const std::vector<std::string>& texts) -> std::map<char, counter_t>;
auto frequency(const std::vector<std::string_view>& texts) -> std::map<char, counter_t>;

}

#endif

