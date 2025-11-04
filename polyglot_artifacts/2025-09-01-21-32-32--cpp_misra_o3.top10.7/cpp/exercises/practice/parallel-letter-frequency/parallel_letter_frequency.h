#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

/*  Count the frequency of letters contained in the supplied texts.
    The counting is case-insensitive and is performed in parallel. */
[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}

#endif

