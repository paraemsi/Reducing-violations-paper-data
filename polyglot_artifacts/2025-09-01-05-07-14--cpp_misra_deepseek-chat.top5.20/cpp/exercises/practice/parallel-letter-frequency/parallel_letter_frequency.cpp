#include "parallel_letter_frequency.h"
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <thread>
#include <mutex>
#include <functional>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Lambda to process a chunk of texts
    auto process_chunk = [&result, &result_mutex](const std::vector<std::string>::const_iterator begin,
                                                  const std::vector<std::string>::const_iterator end) {
        std::map<char, int> local_result;
        
        // Process each text in the chunk
        for (auto it = begin; it != end; ++it) {
            const std::string& text = *it;
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    ++local_result[c];
                }
            }
        }
        
        // Merge local result into global result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& pair : local_result) {
            result[pair.first] += pair.second;
        }
    };
    
    // Determine number of threads to use
    const size_t num_threads = std::thread::hardware_concurrency();
    const size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    
    std::vector<std::thread> threads;
    auto it = texts.begin();
    
    // Start threads to process chunks
    for (size_t i = 0; i < num_threads; ++i) {
        auto chunk_start = it;
        auto chunk_end = (i == num_threads - 1) ? texts.end() : 
                         (it + chunk_size > texts.end() ? texts.end() : it + chunk_size);
        
        if (chunk_start != chunk_end) {
            threads.emplace_back(process_chunk, chunk_start, chunk_end);
            it = chunk_end;
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
