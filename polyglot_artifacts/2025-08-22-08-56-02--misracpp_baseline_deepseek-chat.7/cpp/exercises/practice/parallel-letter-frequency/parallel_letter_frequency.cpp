#include "parallel_letter_frequency.h"
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <cctype>
#include <algorithm>
#include <functional>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Handle empty input
    if (texts.empty()) {
        return result;
    }
    
    // Number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    // To avoid creating more threads than necessary
    num_threads = std::min(num_threads, static_cast<unsigned int>(texts.size()));
    
    // Split the work among threads
    std::vector<std::thread> threads;
    size_t chunk_size = (texts.size() + num_threads - 1) / num_threads; // Ceiling division
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start_index = i * chunk_size;
        size_t end_index = std::min((i + 1) * chunk_size, texts.size());
        
        if (start_index >= end_index) {
            break;
        }
        
        threads.emplace_back([&texts, start_index, end_index, &result, &result_mutex]() {
            // Local frequency map for this thread's chunk
            std::map<char, int> local_freq;
            
            // Process each text in the assigned range
            for (size_t j = start_index; j < end_index; ++j) {
                const std::string& text = texts[j];
                for (char c : text) {
                    if (std::isalpha(static_cast<unsigned char>(c))) {
                        char lower_c = std::tolower(static_cast<unsigned char>(c));
                        local_freq[lower_c]++;
                    }
                }
            }
            
            // Merge with the global result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_freq) {
                result[pair.first] += pair.second;
            }
        });
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
