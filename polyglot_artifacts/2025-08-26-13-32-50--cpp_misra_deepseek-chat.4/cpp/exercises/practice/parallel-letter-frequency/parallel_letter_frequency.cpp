#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <atomic>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, result_int_t> frequency(const std::vector<std::string>& texts) {
    // Alias to use internally to satisfy MISRA rules
    using count_t = std::int32_t;
    
    // Use an array of atomic integers for each letter 'a' to 'z'
    std::array<std::atomic<count_t>, 26> counts;
    // Initialize all atomics to 0
    for (auto& count : counts) {
        count.store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // For each character in the text
            for (char c : text) {
                // Check if it's a letter
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    // Update the corresponding atomic count
                    // Ensure proper parenthesization according to rules
                    count_t index = (static_cast<count_t>(lower_c) - static_cast<count_t>('a'));
                    counts[index].fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    
    // Convert the array to a map
    std::map<char, result_int_t> result;
    for (count_t i = 0; i < 26; ++i) {
        char c = static_cast<char>('a' + i);
        // The result_int_t alias is int, so no cast needed
        result[c] = static_cast<result_int_t>(counts[i].load(std::memory_order_relaxed));
    }
    
    return result;
}

}
