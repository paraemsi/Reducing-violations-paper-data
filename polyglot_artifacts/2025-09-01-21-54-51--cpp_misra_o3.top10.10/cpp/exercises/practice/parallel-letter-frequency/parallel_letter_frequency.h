#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, std::uint32_t>;

/*
 * Calculate total letter frequency for a collection of texts.
 * Each string is processed in parallel; the partial results are
 * merged into a single frequency map that is returned to the caller.
 */
[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}

#endif

