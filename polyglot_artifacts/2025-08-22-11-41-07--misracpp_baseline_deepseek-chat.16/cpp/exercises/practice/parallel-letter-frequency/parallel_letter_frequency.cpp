#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <mutex>
#include <cctype>
#include <vector>
#include <string_view>
#include <map>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    // To reduce lock contention, we can use an array for counts which is faster
    // Since there are only 26 letters, we can use a fixed-size array
    std::map<char, int> result;
    std::mutex result_mutex;
    
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string_view& text) {
            // Use a local array to count frequencies
            int local_counts[26] = {0};
            
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    // Convert to lowercase and count
                    char lower_c = std::tolower(c);
                    local_counts[lower_c - 'a']++;
                }
            }
            
            // Merge into the result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (int i = 0; i < 26; i++) {
                if (local_counts[i] > 0) {
                    result['a' + i] += local_counts[i];
                }
            }
        });
    
    return result;
}

}
