#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <functional>
#include <iterator>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // To follow the rules, we'll use a type alias for the count type
    using CountType = std::int32_t;
    
    // Create a vector to hold individual frequency maps using CountType
    std::vector<std::map<char, CountType>> partial_results(texts.size());
    
    // Process each text in parallel, filling its corresponding map
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&partial_results, &texts](const std::string& text) {
            // Get index of the current text
            // Since text is from the vector, we can use pointer arithmetic to find its index
            // This is valid because vector elements are contiguous
            const auto index = static_cast<std::size_t>((&text) - (&texts[0]));
            auto& local_map = partial_results[index];
            
            for (char c : text) {
                // Cast to unsigned char to avoid UB with std::isalpha and std::tolower
                const unsigned char uc = static_cast<unsigned char>(c);
                if ((std::isalpha(uc)) != 0) {
                    const char lower_c = static_cast<char>(std::tolower(uc));
                    // Use CountType for the increment
                    local_map[lower_c] = static_cast<CountType>(local_map[lower_c] + static_cast<CountType>(1));
                }
            }
        });
    
    // Combine all partial results, converting CountType to int for the result
    std::map<char, int> result;
    for (const auto& partial : partial_results) {
        for (const auto& pair : partial) {
            result[pair.first] = static_cast<int>(result[pair.first] + static_cast<int>(pair.second));
        }
    }
    
    return result;
}

}
