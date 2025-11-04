#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <mutex>
#include <map>
#include <vector>
#include <string>
#include <cctype>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Local counts for this text
            std::map<char, int> local_counts;
            
            // Count only letters, converting to lowercase
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    local_counts[lower_c]++;
                }
            }
            
            // Merge into the result with lock
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& entry : local_counts) {
                result[entry.first] += entry.second;
            }
        });
    
    return result;
}

}
