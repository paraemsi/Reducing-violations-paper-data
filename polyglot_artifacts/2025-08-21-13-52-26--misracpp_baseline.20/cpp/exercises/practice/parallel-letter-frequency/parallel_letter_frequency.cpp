#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <cctype>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> global_freq;
    std::mutex freq_mutex;

    // Determine number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 2;
    num_threads = std::min<unsigned int>(num_threads, texts.size());
    if (num_threads == 0) return global_freq;

    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> local_freqs(num_threads);

    // Partition the texts for each thread
    auto worker = [&](size_t start, size_t end, size_t idx) {
        std::map<char, int>& freq = local_freqs[idx];
        for (size_t i = start; i < end; ++i) {
            for (char ch : texts[i]) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = std::tolower(static_cast<unsigned char>(ch));
                    freq[lower]++;
                }
            }
        }
    };

    size_t chunk_size = texts.size() / num_threads;
    size_t remainder = texts.size() % num_threads;
    size_t start = 0;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t end = start + chunk_size + (t < remainder ? 1 : 0);
        threads.emplace_back(worker, start, end, t);
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    // Merge local frequencies into global
    for (const auto& freq : local_freqs) {
        for (const auto& pair : freq) {
            global_freq[pair.first] += pair.second;
        }
    }

    return global_freq;
}

}
