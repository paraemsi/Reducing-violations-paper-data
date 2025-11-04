#include "parallel_letter_frequency.h"
#include <algorithm>
#include <map>
#include <cctype>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return std::map<char, int>();
    }
    
    // Number of threads to use
    const unsigned int num_threads = std::max(std::thread::hardware_concurrency(), 1u);
    std::vector<std::map<char, int>> thread_results(num_threads);
    std::vector<std::thread> threads;
    
    // Lambda function to process a range of texts
    auto process_range = [&texts](std::map<char, int>& result, size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            const std::string& text = texts[i];
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    char lower_c = std::tolower(c);
                    result[lower_c]++;
                }
            }
        }
    };
    
    // Split work among threads
    size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, texts.size());
        if (start < texts.size()) {
            threads.emplace_back(process_range, 
                                 std::ref(thread_results[i]), 
                                 start, end);
        }
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Merge results from all threads
    std::map<char, int> final_result;
    for (const auto& thread_result : thread_results) {
        for (const auto& pair : thread_result) {
            final_result[pair.first] += pair.second;
        }
    }
    
    return final_result;
}

}
