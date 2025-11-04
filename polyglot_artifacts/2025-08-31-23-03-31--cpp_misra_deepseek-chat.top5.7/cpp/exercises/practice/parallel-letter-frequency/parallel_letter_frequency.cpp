#include "parallel_letter_frequency.h"
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <thread>
#include <mutex>
#include <cstdint>
#include <memory>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    std::map<char, std::int32_t> result;
    // Handle empty input early
    if (texts.empty()) {
        return result;
    }
    
    // Use a mutex to protect access to the result map
    std::mutex result_mutex;
    
    // Determine number of threads to use
    const unsigned int num_threads = std::thread::hardware_concurrency();
    const unsigned int actual_num_threads = (num_threads == 0) ? 1U : num_threads;
    std::vector<std::thread> threads;
    
    // Split work among threads
    const std::size_t total_texts = texts.size();
    const std::size_t chunk_size = (total_texts + actual_num_threads - 1U) / actual_num_threads;
    
    for (unsigned int t = 0U; t < actual_num_threads; t++) {
        const std::size_t start = t * chunk_size;
        if (start >= total_texts) {
            break;
        }
        const std::size_t end = std::min(start + chunk_size, total_texts);
        
        threads.emplace_back(
            [&](std::size_t s, std::size_t e) {
                // Thread-local counts
                std::map<char, std::int32_t> local_counts;
                
                for (std::size_t i = s; i < e; i++) {
                    for (const char c : texts[i]) {
                        // Check if the character is a letter using isalpha
                        // We need to cast to unsigned char to avoid UB
                        const unsigned char uc = static_cast<unsigned char>(c);
                        if (std::isalpha(uc) != 0) {
                            // Convert to lowercase
                            const char lower_c = static_cast<char>(std::tolower(uc));
                            // Update local count
                            local_counts[lower_c] += 1;
                        }
                    }
                }
                
                // Merge with global result
                std::lock_guard<std::mutex> lock(result_mutex);
                for (const auto& pair : local_counts) {
                    result[pair.first] += pair.second;
                }
            },
            start, end
        );
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    return result;
}

}
