#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string_view>& texts);

}

#endif

