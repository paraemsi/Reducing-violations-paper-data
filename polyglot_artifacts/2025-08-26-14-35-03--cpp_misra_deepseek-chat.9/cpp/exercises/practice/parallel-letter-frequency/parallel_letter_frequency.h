#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

namespace parallel_letter_frequency {

// Define a fixed-width integer type without using standard names directly
struct CounterImpl {
    using IntType = std::int32_t;
};
using Counter = CounterImpl::IntType;
std::map<char, Counter> frequency(const std::vector<std::string>& texts);

}

#endif

