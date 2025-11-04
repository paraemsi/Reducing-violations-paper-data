#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <atomic>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Create an array of atomics for each letter 'a' to 'z'
    std::array<std::atomic<int>, 26> counts;
    for (auto& count : counts) {
        count.store(0, std::memory_order_relaxed);
    }
    
    // Create a lookup table to map characters to indices without arithmetic
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            for (char c : text) {
                // Check if it's a letter using isalpha
                if (std::isalpha(static_cast<unsigned char>(c)) != 0) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                    // Use a switch to find the index without character arithmetic
                    int index = -1;
                    switch (lower_c) {
                        case 'a': index = 0; break;
                        case 'b': index = 1; break;
                        case 'c': index = 2; break;
                        case 'd': index = 3; break;
                        case 'e': index = 4; break;
                        case 'f': index = 5; break;
                        case 'g': index = 6; break;
                        case 'h': index = 7; break;
                        case 'i': index = 8; break;
                        case 'j': index = 9; break;
                        case 'k': index = 10; break;
                        case 'l': index = 11; break;
                        case 'm': index = 12; break;
                        case 'n': index = 13; break;
                        case 'o': index = 14; break;
                        case 'p': index = 15; break;
                        case 'q': index = 16; break;
                        case 'r': index = 17; break;
                        case 's': index = 18; break;
                        case 't': index = 19; break;
                        case 'u': index = 20; break;
                        case 'v': index = 21; break;
                        case 'w': index = 22; break;
                        case 'x': index = 23; break;
                        case 'y': index = 24; break;
                        case 'z': index = 25; break;
                        default: index = -1; break;
                    }
                    if (index >= 0) {
                        // Atomically increment the count
                        counts[index].fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        });
    
    // Convert the array to a map
    std::map<char, int> result;
    // Use a switch to generate the characters without arithmetic
    for (int i = 0; i < 26; i++) {
        char c;
        switch (i) {
            case 0: c = 'a'; break;
            case 1: c = 'b'; break;
            case 2: c = 'c'; break;
            case 3: c = 'd'; break;
            case 4: c = 'e'; break;
            case 5: c = 'f'; break;
            case 6: c = 'g'; break;
            case 7: c = 'h'; break;
            case 8: c = 'i'; break;
            case 9: c = 'j'; break;
            case 10: c = 'k'; break;
            case 11: c = 'l'; break;
            case 12: c = 'm'; break;
            case 13: c = 'n'; break;
            case 14: c = 'o'; break;
            case 15: c = 'p'; break;
            case 16: c = 'q'; break;
            case 17: c = 'r'; break;
            case 18: c = 's'; break;
            case 19: c = 't'; break;
            case 20: c = 'u'; break;
            case 21: c = 'v'; break;
            case 22: c = 'w'; break;
            case 23: c = 'x'; break;
            case 24: c = 'y'; break;
            case 25: c = 'z'; break;
            default: continue;
        }
        result[c] = counts[i].load(std::memory_order_relaxed);
    }
    return result;
}

}
