#include "parallel_letter_frequency.h"
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <cctype>
#include <functional>
#include <algorithm>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return {};
    }

    // Determine the number of threads to use
    const unsigned int num_threads = std::max(std::thread::hardware_concurrency(), 1u);
    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> thread_results(num_threads);
    
    // Split the work among threads
    const std::size_t total_texts = texts.size();
    const std::size_t chunk_size = (total_texts + num_threads - 1) / num_threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        const std::size_t start = i * chunk_size;
        if (start >= total_texts) {
            break;
        }
        const std::size_t end = std::min(start + chunk_size, total_texts);
        
        // Start a thread to process its chunk of texts
        threads.emplace_back([&texts, start, end, &thread_results, i]() {
            auto& local_freq = thread_results[i];
            for (std::size_t j = start; j < end; ++j) {
                const std::string& text = texts[j];
                for (char c : text) {
                    if (std::isalpha(static_cast<unsigned char>(c))) {
                        char lower_c = std::tolower(static_cast<unsigned char>(c));
                        local_freq[lower_c]++;
                    }
                }
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Merge all thread results
    std::map<char, int> result;
    for (const auto& local_freq : thread_results) {
        for (const auto& entry : local_freq) {
            result[entry.first] += entry.second;
        }
    }
    
    return result;
}

}
