#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <cctype>
#include <algorithm>
#include <functional>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return std::map<char, int>();
    }

    // Determine number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    num_threads = std::min(num_threads, static_cast<unsigned int>(texts.size()));
    
    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> thread_results(num_threads);
    
    // Distribute work among threads
    auto worker = [&texts](std::map<char, int>& result, size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            const std::string_view& text = texts[i];
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    result[std::tolower(static_cast<unsigned char>(c))]++;
                }
            }
        }
    };
    
    // Start threads
    size_t chunk_size = texts.size() / num_threads;
    size_t remainder = texts.size() % num_threads;
    size_t start = 0;
    
    for (size_t i = 0; i < num_threads; ++i) {
        size_t end = start + chunk_size + (i < remainder ? 1 : 0);
        threads.emplace_back(worker, std::ref(thread_results[i]), start, end);
        start = end;
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Combine results from all threads
    std::map<char, int> final_result;
    for (const auto& partial_result : thread_results) {
        for (const auto& entry : partial_result) {
            final_result[entry.first] += entry.second;
        }
    }
    
    return final_result;
}

}
