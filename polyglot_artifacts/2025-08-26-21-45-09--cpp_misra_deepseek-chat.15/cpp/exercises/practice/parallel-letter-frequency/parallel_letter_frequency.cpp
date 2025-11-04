#include "parallel_letter_frequency.h"
#include <map>
#include <vector>
#include <string>
#include <mutex>
#include <cctype>
#include <algorithm>
#include <execution>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    std::map<char, std::int32_t> result;
    std::mutex result_mutex;
    
    // Use parallel for_each to process each text
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Process each character in the text
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    // Lock the mutex to update the result
                    std::lock_guard<std::mutex> lock(result_mutex);
                    result[lower_c] += 1;
                }
            }
        });
    
    return result;
}

}
