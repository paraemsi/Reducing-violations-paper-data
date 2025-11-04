#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <unordered_map>
#include <vector>
#include <string_view>
#include <cstdint>

namespace parallel_letter_frequency {

// Note: Using char as map key is required by the test interface
// The char is used only as a key (for equality comparison), not for arithmetic
using frequency_map = std::unordered_map<char, std::int32_t>;

frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif
