#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <atomic>
#include <array>
#include <functional>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Create an array of atomics for each lowercase letter
    std::array<std::atomic<int>, 26> freqs;
    for (int i = 0; i < 26; ++i) {
        freqs[i].store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // For each character in the text, update the corresponding atomic counter
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    // Convert to lowercase
                    c = std::tolower(c);
                    // 'a' is at index 0, 'b' at 1, etc.
                    int index = c - 'a';
                    // Atomically increment the counter
                    freqs[index].fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    
    // Build the result map
    std::map<char, int> result;
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + i;
        result[c] = freqs[i].load(std::memory_order_relaxed);
    }
    return result;
}

}
