#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*  Alias for the resulting frequency map                                   */
using frequency_map = std::map<char, std::uint32_t>;

/*  Calculate the total letter frequency for the given collection of texts. */
frequency_map frequency(const std::vector<std::string_view>& texts);

} // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

