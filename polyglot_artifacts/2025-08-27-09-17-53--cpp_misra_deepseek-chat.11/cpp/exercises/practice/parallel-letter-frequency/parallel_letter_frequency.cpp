#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <functional>
#include <mutex>
#include <cstdint>
#include <numeric>
#include <utility>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    std::map<char, std::int32_t> result;
    std::mutex result_mutex;
    
    // Process each text in parallel and update the result map
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Count letters in this text
            std::map<char, std::int32_t> local_counts;
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    ++local_counts[c];
                }
            }
            
            // Merge into the result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
