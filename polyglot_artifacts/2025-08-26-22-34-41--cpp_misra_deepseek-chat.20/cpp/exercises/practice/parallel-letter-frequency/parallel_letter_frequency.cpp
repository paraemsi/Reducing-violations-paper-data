#include "parallel_letter_frequency.h"
#include <map>
#include <mutex>
#include <cctype>
#include <vector>
#include <string>
#include <thread>
#include <functional>
#include <memory>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Handle empty input
    if (texts.empty()) {
        return std::map<char, int>();
    }
    
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Number of threads to use - ensure at least 1
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    
    std::vector<std::thread> threads;
    
    // Function to process a range of texts
    auto process_range = [&](size_t start, size_t end) {
        std::map<char, int> local_counts;
        for (size_t i = start; i < end; ++i) {
            const std::string& text = texts[i];
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    char lower_c = static_cast<char>(std::tolower(c));
                    local_counts[lower_c]++;
                }
            }
        }
        
        // Merge with the global result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& pair : local_counts) {
            result[pair.first] += pair.second;
        }
    };
    
    // Distribute work among threads
    const size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, texts.size());
        if (start < end) {
            threads.emplace_back(process_range, start, end);
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
