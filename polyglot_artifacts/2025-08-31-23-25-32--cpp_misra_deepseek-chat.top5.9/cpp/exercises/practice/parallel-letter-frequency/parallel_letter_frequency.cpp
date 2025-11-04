#include "parallel_letter_frequency.h"
#include <cctype>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) { 
        return {}; 
    }
    
    // Use uint32_t for sizes to follow MISRA rules
    const std::uint32_t num_threads = static_cast<std::uint32_t>(std::thread::hardware_concurrency());
    const std::uint32_t texts_size = static_cast<std::uint32_t>(texts.size());
    const std::uint32_t chunk_size = ((texts_size + (num_threads - 1)) / num_threads);
    
    // Result map and mutex to protect it
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Function to process a range of texts
    auto process_chunk = [&result, &result_mutex](const std::vector<std::string>::const_iterator begin,
                                                  const std::vector<std::string>::const_iterator end) {
        std::map<char, int> local_freq;
        for (auto it = begin; it != end; ++it) {
            for (const auto& c : *it) {
                // Check if the character is alphabetic using isalpha
                // Cast to unsigned char to avoid UB
                if (std::isalpha(static_cast<unsigned char>(c)) != 0) {
                    // Convert to lowercase
                    // Note: According to MISRA, we shouldn't use the numerical value of characters,
                    // but tolower is a standard function that operates on character values
                    // We'll cast to unsigned char to avoid UB, then back to char
                    const char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                    // Since we're only doing equality comparisons, this should be fine
                    local_freq[lower_c] += 1;
                }
            }
        }
        
        // Merge with the global result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& pair : local_freq) {
            result[pair.first] += pair.second;
        }
    };
    
    // Create and run threads
    std::vector<std::thread> threads;
    auto it = texts.begin();
    for (std::uint32_t i = 0; i < num_threads; ++i) {
        const auto start = it;
        // Determine the end iterator
        auto end = texts.end();
        if (i < (num_threads - 1)) {
            // Advance the iterator by chunk_size, but not beyond the end
            const std::uint32_t remaining = static_cast<std::uint32_t>(texts.end() - it);
            if (chunk_size < remaining) {
                end = it + chunk_size;
            }
        }
        if (start == end) {
            break;
        }
        threads.emplace_back(process_chunk, start, end);
        it = end;
        if (it == texts.end()) {
            break;
        }
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    
    return result;
}

}
