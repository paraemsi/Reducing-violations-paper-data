#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <cctype>
#include <mutex>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Create a result map
    std::map<char, int> result;
    
    // To protect access to the result map from multiple threads
    std::mutex result_mutex;
    
    // Use parallel for_each to process each text
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Create a local frequency map for this text
            std::map<char, int> local_freq;
            
            // Count frequencies in the current text
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    char lower_c = std::tolower(c);
                    local_freq[lower_c]++;
                }
            }
            
            // Safely merge local frequencies into the result
            // Lock the mutex to prevent data races
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& entry : local_freq) {
                result[entry.first] += entry.second;
            }
        }
    );
    
    return result;
}

}
