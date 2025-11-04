#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

using text_t = std::string;
using frequency_map_t = std::map<char, std::uint32_t>;

// MISRA: Use alias for vector of text_t
using text_vector_t = std::vector<text_t>;

// Forward declaration for letter_frequency
frequency_map_t letter_frequency(const text_vector_t& texts);

// Provide alias 'frequency' for backward compatibility with test suite
frequency_map_t frequency(const text_vector_t& texts);

}

#endif

