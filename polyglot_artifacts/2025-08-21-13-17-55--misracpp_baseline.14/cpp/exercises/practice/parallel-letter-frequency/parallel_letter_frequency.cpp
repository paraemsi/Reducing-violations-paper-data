#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <cctype>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> global_freq;
    std::mutex freq_mutex;

    auto worker = [&](size_t start, size_t end, std::map<char, int>& local_freq) {
        for (size_t i = start; i < end; ++i) {
            for (char ch : texts[i]) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = std::tolower(static_cast<unsigned char>(ch));
                    ++local_freq[lower];
                }
            }
        }
    };

    unsigned int num_threads = std::min<unsigned int>(std::thread::hardware_concurrency(), texts.size());
    if (num_threads == 0) num_threads = 1;

    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> local_freqs(num_threads);

    size_t block_size = texts.size() / num_threads;
    size_t remainder = texts.size() % num_threads;
    size_t start = 0;

    for (unsigned int t = 0; t < num_threads; ++t) {
        size_t end = start + block_size + (t < remainder ? 1 : 0);
        threads.emplace_back(worker, start, end, std::ref(local_freqs[t]));
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    // Merge local maps into global map
    for (const auto& local : local_freqs) {
        for (const auto& pair : local) {
            global_freq[pair.first] += pair.second;
        }
    }

    return global_freq;
}

}
