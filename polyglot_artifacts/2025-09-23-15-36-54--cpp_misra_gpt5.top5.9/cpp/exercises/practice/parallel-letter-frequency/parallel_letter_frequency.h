#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Type for counts, avoiding plain int per MISRA guidance.
using count_type = std::uint32_t;

// Deterministic ordering by key can help with predictable comparisons in tests.
using frequency_map = std::map<char, count_type>;

// Compute letter frequencies across all texts using a reasonable default
// level of parallelism (based on hardware concurrency).
auto frequency(const std::vector<std::string>& texts) -> frequency_map;

// Compute letter frequencies using an explicit number of worker tasks.
auto frequency(const std::vector<std::string>& texts, std::size_t worker_count) -> frequency_map;

// Overloads accepting string_view to match test inputs without copying.
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;
auto frequency(const std::vector<std::string_view>& texts, std::size_t worker_count) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

