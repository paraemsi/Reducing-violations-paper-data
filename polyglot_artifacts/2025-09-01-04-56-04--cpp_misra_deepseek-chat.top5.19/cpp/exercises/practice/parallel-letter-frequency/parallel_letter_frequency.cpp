#include "parallel_letter_frequency.h"
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cctype>
#include <cstdint>
#include <functional>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    std::map<char, std::int32_t> result;
    std::mutex result_mutex;
    
    // Number of threads to use
    const size_t num_threads = std::thread::hardware_concurrency();
    const size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    
    // Lambda to process a range of texts
    auto process_range = [&](size_t start, size_t end) {
        // Local count for this range
        std::map<char, std::int32_t> local_counts;
        for (size_t i = start; (i < end) && (i < texts.size()); ++i) {
            const std::string& text = texts[i];
            for (const char c : text) {
                // Convert to unsigned char to use with ctype functions
                const unsigned char uc = static_cast<unsigned char>(c);
                // Check if the character is alphabetic using isalpha
                if ((std::isalpha(uc) != 0)) {
                    // Convert to lowercase
                    const char lower_c = static_cast<char>(std::tolower(uc));
                    // Update count
                    local_counts[lower_c] = (local_counts[lower_c] + static_cast<std::int32_t>(1));
                }
            }
        }
        
        // Merge local counts into the result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& pair : local_counts) {
            result[pair.first] = (result[pair.first] + pair.second);
        }
    };
    
    // Create and manage threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = start + chunk_size;
        threads.emplace_back(process_range, start, end);
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    return result;
}

}
