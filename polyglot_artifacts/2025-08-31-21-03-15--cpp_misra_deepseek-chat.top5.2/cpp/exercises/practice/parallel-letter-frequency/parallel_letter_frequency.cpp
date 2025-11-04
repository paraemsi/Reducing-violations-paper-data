#include "parallel_letter_frequency.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <execution>
#include <cctype>
#include <functional>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Handle empty input
    if (texts.empty()) { 
        return std::map<char, int>(); 
    }
    
    // To follow MISRA rules, we need to use fixed-width integers internally
    // We'll use a map with int32_t which should be compatible with int on most platforms
    using CountMap = std::map<char, std::int32_t>;
    
    // Process each text in parallel and reduce the results
    CountMap result_map = std::transform_reduce(
        std::execution::par,
        texts.begin(),
        texts.end(),
        CountMap(),
        // Binary operation to reduce partial results
        [](CountMap lhs, const CountMap& rhs) -> CountMap {
            for (const auto& pair : rhs) {
                // Add counts from rhs to lhs
                lhs[pair.first] += pair.second;
            }
            return lhs;
        },
        // Unary operation to process each text
        [](const std::string& text) -> CountMap {
            CountMap local_count;
            for (const char c : text) {
                // Cast to unsigned char for ctype functions
                const unsigned char uc = static_cast<unsigned char>(c);
                // Check if the character is a letter
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    const char lower_c = static_cast<char>(std::tolower(uc));
                    // Increment count
                    local_count[lower_c] += static_cast<std::int32_t>(1);
                }
            }
            return local_count;
        }
    );
    
    // Convert to the required return type
    std::map<char, int> result;
    for (const auto& pair : result_map) {
        result[pair.first] = static_cast<int>(pair.second);
    }
    return result;
}

}
