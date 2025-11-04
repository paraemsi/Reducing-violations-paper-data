#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {


frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hw_threads =
        std::max<unsigned int>(1, std::thread::hardware_concurrency());
    const std::size_t thread_count =
        std::min<std::size_t>(hw_threads, texts.size());

    std::vector<frequency_map> local_counts(thread_count);
    std::vector<std::thread>   workers;
    workers.reserve(thread_count);

    const std::size_t block_size = texts.size() / thread_count;
    const std::size_t remainder  = texts.size() % thread_count;

    auto worker = [&texts](std::size_t begin,
                           std::size_t end,
                           frequency_map& local) {
        for (std::size_t i = begin; i < end; ++i) {
            for (unsigned char ch : texts[i]) {           // prevent UB in isalpha
                if (std::isalpha(ch)) {
                    ch = static_cast<unsigned char>(std::tolower(ch));
                    ++local[static_cast<char>(ch)];
                }
            }
        }
    };

    std::size_t index = 0;
    for (std::size_t t = 0; t < thread_count; ++t) {
        const std::size_t begin = index;
        const std::size_t end   = begin + block_size + (t < remainder ? 1 : 0);
        index                   = end;
        workers.emplace_back(worker, begin, end, std::ref(local_counts[t]));
    }

    for (auto& th : workers) {
        th.join();
    }

    frequency_map result;
    for (const auto& local : local_counts) {
        for (const auto& [letter, count] : local) {
            result[letter] += count;
        }
    }
    return result;
}

// convenience overload for std::string inputs
frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}  // namespace parallel_letter_frequency
