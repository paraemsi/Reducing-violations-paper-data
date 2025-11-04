#include "parallel_letter_frequency.h"
#include <vector>
#include <string>
#include <algorithm>
#include <execution>
#include <cctype>
#include <map>
#include <array>
#include <thread>
#include <mutex>
#include <cstdint>
#include <cstddef>

namespace parallel_letter_frequency {

std::map<char, count_type> frequency(const std::vector<std::string>& texts) {
    // Define a type alias for the index type
    using index_type = std::int32_t;
    
    // Use an array for each letter 'a' to 'z' with fixed-width integer type
    std::array<count_type, 26> total_freq{};
    std::mutex mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Local frequency counter for this text
            std::array<count_type, 26> local_freq{};
            
            // Count frequencies in the current text
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    // Add parentheses to ensure proper precedence
                    index_type index = static_cast<index_type>((lower_c - 'a'));
                    local_freq[static_cast<std::size_t>(index)]++;
                }
            }
            
            // Lock the mutex to update the total frequencies
            std::lock_guard<std::mutex> lock(mutex);
            for (index_type i = 0; i < 26; i++) {
                total_freq[static_cast<std::size_t>(i)] = 
                    (total_freq[static_cast<std::size_t>(i)] + local_freq[static_cast<std::size_t>(i)]);
            }
        });
    
    // Convert the array to a map
    std::map<char, count_type> result;
    for (index_type i = 0; i < 26; i++) {
        if ((total_freq[static_cast<std::size_t>(i)] > 0)) {
            result[static_cast<char>(('a' + i))] = total_freq[static_cast<std::size_t>(i)];
        }
    }
    return result;
}

}
