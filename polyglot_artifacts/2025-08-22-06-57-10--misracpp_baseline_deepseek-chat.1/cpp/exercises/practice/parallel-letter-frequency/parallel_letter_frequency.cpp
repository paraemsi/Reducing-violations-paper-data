#include "parallel_letter_frequency.h"
#include <map>
#include <mutex>
#include <vector>
#include <cctype>
#include <string_view>
#include <thread>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Determine number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 1;
    num_threads = std::min(num_threads, static_cast<unsigned int>(texts.size()));
    
    // Split work among threads
    std::vector<std::thread> threads;
    size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, texts.size());
        if (start >= end) continue;
        
        threads.emplace_back([&result, &result_mutex, &texts, start, end]() {
            // Local count for this thread's chunk
            std::map<char, int> local_count;
            
            for (size_t j = start; j < end; ++j) {
                const std::string_view& text = texts[j];
                for (char c : text) {
                    if (std::isalpha(static_cast<unsigned char>(c))) {
                        char lower_c = std::tolower(static_cast<unsigned char>(c));
                        local_count[lower_c]++;
                    }
                }
            }
            
            // Merge with the global result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_count) {
                result[pair.first] += pair.second;
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    return result;
}

}
