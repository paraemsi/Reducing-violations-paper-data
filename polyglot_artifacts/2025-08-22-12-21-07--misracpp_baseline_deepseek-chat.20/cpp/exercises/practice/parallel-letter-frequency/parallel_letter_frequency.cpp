#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <execution>
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <thread>
#include <functional>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Number of threads to use
    const size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::map<char, int>> thread_maps(num_threads);
    std::vector<std::thread> threads;
    
    // Split the work among threads
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([i, num_threads, &texts, &thread_maps]() {
            auto& local_map = thread_maps[i];
            // Process every num_threads-th text starting from i
            for (size_t j = i; j < texts.size(); j += num_threads) {
                const auto& text = texts[j];
                for (char c : text) {
                    if (std::isalpha(static_cast<unsigned char>(c))) {
                        char lower_c = std::tolower(static_cast<unsigned char>(c));
                        local_map[lower_c]++;
                    }
                }
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Merge all thread-local maps
    std::map<char, int> result;
    for (const auto& thread_map : thread_maps) {
        for (const auto& pair : thread_map) {
            result[pair.first] += pair.second;
        }
    }
    
    return result;
}

}
