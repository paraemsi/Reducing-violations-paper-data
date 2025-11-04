#include "parallel_letter_frequency.h"
#include <atomic>
#include <algorithm>
#include <execution>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    // Create an array of atomic integers for each letter (case-insensitive)
    std::atomic<std::int32_t> counts[26] = {};
    // Initialize each atomic
    for (std::int32_t i = 0; i < 26; ++i) {
        counts[i] = 0;
    }

    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&counts](const std::string& text) {
            for (char c : text) {
                // Check if it's a letter using unsigned char to avoid UB
                unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(uc));
                    
                    // Use a switch statement to find the right counter to increment
                    // This avoids using numerical values of characters
                    switch (lower_c) {
                        case 'a': counts[0].fetch_add(1, std::memory_order_relaxed); break;
                        case 'b': counts[1].fetch_add(1, std::memory_order_relaxed); break;
                        case 'c': counts[2].fetch_add(1, std::memory_order_relaxed); break;
                        case 'd': counts[3].fetch_add(1, std::memory_order_relaxed); break;
                        case 'e': counts[4].fetch_add(1, std::memory_order_relaxed); break;
                        case 'f': counts[5].fetch_add(1, std::memory_order_relaxed); break;
                        case 'g': counts[6].fetch_add(1, std::memory_order_relaxed); break;
                        case 'h': counts[7].fetch_add(1, std::memory_order_relaxed); break;
                        case 'i': counts[8].fetch_add(1, std::memory_order_relaxed); break;
                        case 'j': counts[9].fetch_add(1, std::memory_order_relaxed); break;
                        case 'k': counts[10].fetch_add(1, std::memory_order_relaxed); break;
                        case 'l': counts[11].fetch_add(1, std::memory_order_relaxed); break;
                        case 'm': counts[12].fetch_add(1, std::memory_order_relaxed); break;
                        case 'n': counts[13].fetch_add(1, std::memory_order_relaxed); break;
                        case 'o': counts[14].fetch_add(1, std::memory_order_relaxed); break;
                        case 'p': counts[15].fetch_add(1, std::memory_order_relaxed); break;
                        case 'q': counts[16].fetch_add(1, std::memory_order_relaxed); break;
                        case 'r': counts[17].fetch_add(1, std::memory_order_relaxed); break;
                        case 's': counts[18].fetch_add(1, std::memory_order_relaxed); break;
                        case 't': counts[19].fetch_add(1, std::memory_order_relaxed); break;
                        case 'u': counts[20].fetch_add(1, std::memory_order_relaxed); break;
                        case 'v': counts[21].fetch_add(1, std::memory_order_relaxed); break;
                        case 'w': counts[22].fetch_add(1, std::memory_order_relaxed); break;
                        case 'x': counts[23].fetch_add(1, std::memory_order_relaxed); break;
                        case 'y': counts[24].fetch_add(1, std::memory_order_relaxed); break;
                        case 'z': counts[25].fetch_add(1, std::memory_order_relaxed); break;
                        default: break;
                    }
                }
            }
        });

    // Build the result map
    std::map<char, std::int32_t> result;
    result['a'] = counts[0].load();
    result['b'] = counts[1].load();
    result['c'] = counts[2].load();
    result['d'] = counts[3].load();
    result['e'] = counts[4].load();
    result['f'] = counts[5].load();
    result['g'] = counts[6].load();
    result['h'] = counts[7].load();
    result['i'] = counts[8].load();
    result['j'] = counts[9].load();
    result['k'] = counts[10].load();
    result['l'] = counts[11].load();
    result['m'] = counts[12].load();
    result['n'] = counts[13].load();
    result['o'] = counts[14].load();
    result['p'] = counts[15].load();
    result['q'] = counts[16].load();
    result['r'] = counts[17].load();
    result['s'] = counts[18].load();
    result['t'] = counts[19].load();
    result['u'] = counts[20].load();
    result['v'] = counts[21].load();
    result['w'] = counts[22].load();
    result['x'] = counts[23].load();
    result['y'] = counts[24].load();
    result['z'] = counts[25].load();
    return result;
}

}
