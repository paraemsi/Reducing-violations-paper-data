#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*
 * Calculate the frequency of each alphabetic letter contained in the
 * supplied collection of texts.  All alphabetic characters are treated
 * case-insensitively and accumulated as lower-case values.  Non-alphabetic
 * characters are ignored.
 *
 * The computation may be performed in parallel.  The caller may optionally
 * specify the maximum number of worker threads that shall be spawned;
 * a value of 0 means “use an implementation-defined sensible default”.
 *
 * The returned associative container maps the character key to the
 * number of occurrences observed across the whole input.
 */
[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts,
                             std::uint32_t                       max_workers = 0U)
    -> std::map<char, std::uint32_t>;

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

