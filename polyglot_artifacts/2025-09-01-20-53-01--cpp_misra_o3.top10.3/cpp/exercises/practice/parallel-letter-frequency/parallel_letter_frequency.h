#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace parallel_letter_frequency {

using frequency_map = std::unordered_map<char, std::uint32_t>;

/*
 * Calculate the frequency of each letter (case-insensitive, Latin alphabet)
 * contained in the supplied collection of texts.  The work is divided across
 * several threads to improve throughput on multi-core systems.
 */
[[nodiscard]] auto frequency(const std::vector<std::string>& texts) -> frequency_map;
[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

} // namespace parallel_letter_frequency

