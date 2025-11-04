#include "parallel_letter_frequency.h"

#include <cctype>
#include <mutex>
#include <thread>
#include <string_view>

namespace parallel_letter_frequency {

    // Thin wrapper that converts the std::string inputs to std::string_view
    // and re-uses the real implementation below. This avoids code duplication
    // while still providing the required overload for the tests.
    std::map<char, int> frequency(const std::vector<std::string>& texts) {
        std::vector<std::string_view> views;
        views.reserve(texts.size());
        for (const auto& s : texts) {
            views.emplace_back(s);
        }
        return frequency(views);
    }

    std::map<char, int> frequency(const std::vector<std::string_view>& texts) {

        std::map<char, int> global_result;
        if (texts.empty()) {
            return global_result;
        }

        const std::size_t hardware_threads = std::thread::hardware_concurrency() == 0
                                             ? 2
                                             : std::thread::hardware_concurrency();
        const std::size_t num_threads = std::min<std::size_t>(hardware_threads, texts.size());

        std::mutex result_mutex;
        std::vector<std::thread> workers;
        workers.reserve(num_threads);

        auto worker = [&](std::size_t start, std::size_t end) {
            std::map<char, int> local_counts;
            for (std::size_t i = start; i < end; ++i) {
                for (unsigned char ch : texts[i]) {
                    if (std::isalpha(ch)) {
                        char lower = static_cast<char>(std::tolower(ch));
                        ++local_counts[lower];
                    }
                }
            }
            {
                std::lock_guard<std::mutex> lock(result_mutex);
                for (const auto& [ch, cnt] : local_counts) {
                    global_result[ch] += cnt;
                }
            }
        };

        const std::size_t block_size = texts.size() / num_threads;
        std::size_t start = 0;
        for (std::size_t t = 0; t < num_threads; ++t) {
            std::size_t end = (t == num_threads - 1) ? texts.size() : start + block_size;
            workers.emplace_back(worker, start, end);
            start = end;
        }

        for (auto& th : workers) {
            th.join();
        }

        return global_result;
    }

}
