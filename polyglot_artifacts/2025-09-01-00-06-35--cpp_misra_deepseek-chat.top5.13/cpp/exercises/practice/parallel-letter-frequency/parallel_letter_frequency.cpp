#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <atomic>
#include <cctype>
#include <vector>
#include <functional>
#include <cstdint>
#include <map>

namespace parallel_letter_frequency {

FrequencyMap frequency(const std::vector<std::string>& texts) {
    // Define a fixed-width type to use internally
    using count_type = std::int32_t;
    
    // Create a lookup table to map each lowercase letter to an index without using numerical values
    const unsigned char letters[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    std::map<unsigned char, count_type> char_to_index;
    for (count_type i = 0; i < 26; i++) {
        char_to_index[letters[i]] = i;
    }

    // Create an array of atomics for each letter using our fixed-width type
    std::atomic<count_type> frequencies[26] = {};
    for (count_type i = 0; i < 26; i++) {
        frequencies[i].store(0);
    }

    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            for (char c : text) {
                // Cast to unsigned char for ctype functions
                unsigned char uc = static_cast<unsigned char>(c);
                // Check if it's alphabetic using isalpha
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    unsigned char lower_uc = static_cast<unsigned char>(std::tolower(uc));
                    // Find the index using the lookup table
                    auto it = char_to_index.find(lower_uc);
                    if (it != char_to_index.end()) {
                        count_type index = it->second;
                        // Use parentheses to ensure precedence
                        frequencies[index].fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        });

    // Convert to a map using the letters array to avoid numerical values
    FrequencyMap result;
    for (count_type i = 0; i < 26; i++) {
        // Cast to char to match the map key type
        char c = static_cast<char>(letters[i]);
        count_type count = frequencies[i].load();
        // Check if count is greater than 0
        if (count > 0) {
            // Cast to int to match the test expectations
            result[c] = static_cast<int>(count);
        }
    }
    return result;
}

}
