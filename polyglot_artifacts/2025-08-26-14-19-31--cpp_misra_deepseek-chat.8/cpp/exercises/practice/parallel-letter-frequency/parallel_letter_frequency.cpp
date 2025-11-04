#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <mutex>
#include <cctype>
#include <cstdint>
#include <vector>
#include <string>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // To follow the rules, we'll use a fixed-width integer type internally
    // and cast to int when adding to the result
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Use a local map with std::int32_t to follow the rules
            std::map<char, std::int32_t> local_count;
            for (char c : text) {
                // Check if the character is a letter using unsigned char to avoid UB
                const unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    const char lower_c = static_cast<char>(std::tolower(uc));
                    // Follow rules by using parentheses
                    local_count[lower_c] = (local_count[lower_c] + static_cast<std::int32_t>(1));
                }
            }
            
            // Merge local_count into result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_count) {
                // Cast to int to match the return type, ensuring no narrowing
                // Since std::int32_t and int are typically the same size
                result[pair.first] = (result[pair.first] + static_cast<int>(pair.second));
            }
        });
    
    return result;
}

}
