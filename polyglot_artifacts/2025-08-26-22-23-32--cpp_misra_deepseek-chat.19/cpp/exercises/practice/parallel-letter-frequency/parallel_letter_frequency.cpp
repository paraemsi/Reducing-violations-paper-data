#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <string_view>
#include <cctype>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    // The result must be std::map<char, int> to match the return type
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string_view& text) {
            // Use a local map with int32_t to follow the rules
            std::map<char, std::int32_t> local_counts;
            
            // Count frequencies in the current text
            for (char c : text) {
                // Cast to unsigned char for ctype functions
                unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(uc));
                    // Use parentheses to ensure proper precedence
                    local_counts[lower_c] = (local_counts[lower_c] + 1);
                }
            }
            
            // Merge local_counts into the result map
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                // Cast to int to match result's value type
                result[pair.first] = (result[pair.first] + static_cast<int>(pair.second));
            }
        });
    
    return result;
}

}
