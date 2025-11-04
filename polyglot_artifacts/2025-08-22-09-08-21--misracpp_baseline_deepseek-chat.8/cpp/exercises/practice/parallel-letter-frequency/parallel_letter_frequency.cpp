#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <mutex>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&result, &result_mutex](const std::string& text) {
            // Create a local map to count letters in this text
            std::map<char, int> local_counts;
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    // Convert to lowercase before counting
                    char lower_c = std::tolower(c);
                    local_counts[lower_c]++;
                }
            }
            
            // Merge local_counts into the result map
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& entry : local_counts) {
                result[entry.first] += entry.second;
            }
        });
    
    return result;
}

}
