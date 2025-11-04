#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <mutex>

namespace parallel_letter_frequency {

std::map<char_t, frequency_t> frequency(const std::vector<std::string>& texts) {
    std::map<char_t, frequency_t> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Create a local map to count frequencies for this text
            std::map<char_t, frequency_t> local_counts;
            for (char_t c : text) {
                // Check if the character is a letter by comparing to character literals
                // This avoids using numerical values of characters
                if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) {
                    // Use compound statement
                    local_counts[c] += static_cast<frequency_t>(1);
                }
            }
            
            // Merge local_counts into the result map
            // Use a lock to protect access to the shared result map
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
