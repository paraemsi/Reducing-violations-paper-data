#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <mutex>
#include <thread>
#include <memory>
#include <iterator>
#include <atomic>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // To store the result
    std::map<char, int> result;
    // Mutex to protect access to the result
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Local count for this text
            std::map<char, int> local_counts;
            for (char c : text) {
                // Check if it's a letter
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    local_counts[c]++;
                }
            }
            
            // Merge into the result with a lock
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& entry : local_counts) {
                result[entry.first] += entry.second;
            }
        });
    
    return result;
}

}
