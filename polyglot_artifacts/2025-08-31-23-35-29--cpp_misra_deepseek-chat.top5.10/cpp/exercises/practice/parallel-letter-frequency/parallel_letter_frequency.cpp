#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <cctype>
#include <vector>
#include <string>
#include <atomic>
#include <functional>
#include <iterator>
#include <array>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Use a fixed-size array of atomics
    // Initialize them properly
    std::array<std::atomic<int>, 26> frequencies;
    for (auto& freq : frequencies) {
        freq.store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&frequencies](const std::string& text) {
            // Process each character in the text
            for (unsigned char uc : text) {
                if (std::isalpha(uc)) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(uc));
                    int index = lower_c - 'a';
                    // Ensure index is within bounds
                    if (index >= 0 && index < 26) {
                        frequencies[index].fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        }
    );
    
    // Build the result map
    std::map<char, int> result;
    for (int i = 0; i < 26; i++) {
        char current_char = static_cast<char>('a' + i);
        result[current_char] = frequencies[i].load(std::memory_order_relaxed);
    }
    return result;
}

}
