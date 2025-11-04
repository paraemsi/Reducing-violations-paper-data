#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <mutex>
#include <cctype>
#include <map>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string_view& text) {
            // Create a local map to count frequencies for this text
            std::map<char, int> local_counts;
            for (char c : text) {
                // Check if it's a letter
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase to count 'A' and 'a' as the same
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    local_counts[lower_c]++;
                }
            }
            
            // Merge local_counts into the result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
