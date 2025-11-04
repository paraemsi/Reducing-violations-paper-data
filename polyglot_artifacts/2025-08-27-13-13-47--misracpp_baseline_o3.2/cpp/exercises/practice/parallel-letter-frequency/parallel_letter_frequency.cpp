#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <thread>
#include <unordered_map>

namespace parallel_letter_frequency {


frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    std::size_t num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    num_threads = std::min<std::size_t>(num_threads, texts.size());
    if (num_threads == 0) {
        num_threads = 1;
    }

    std::vector<std::unordered_map<char, int>> partials(num_threads);
    std::vector<std::thread> workers;
    workers.reserve(num_threads);

    const std::size_t chunk_size = texts.size() / num_threads;
    const std::size_t remainder  = texts.size() % num_threads;

    auto process_range = [&](std::size_t start, std::size_t end, std::unordered_map<char, int>& local) {
        for (std::size_t i = start; i < end; ++i) {
            for (unsigned char ch : texts[i]) {
                if (std::isalpha(ch)) {
                    char lower = static_cast<char>(std::tolower(ch));
                    ++local[lower];
                }
            }
        }
    };

    std::size_t begin = 0;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end = begin + chunk_size + (t < remainder ? 1 : 0);
        workers.emplace_back(process_range, begin, end, std::ref(partials[t]));
        begin = end;
    }

    for (auto& th : workers) {
        th.join();
    }

    std::unordered_map<char, int> combined;
    for (const auto& partial : partials) {
        for (const auto& [ch, cnt] : partial) {
            combined[ch] += cnt;
        }
    }

    frequency_map result(combined.begin(), combined.end());
    return result;
}

} // namespace parallel_letter_frequency
