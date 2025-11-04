#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <string_view>

namespace parallel_letter_frequency {

std::unordered_map<char, int> frequency(const std::vector<std::string_view>& texts);

}

#endif

