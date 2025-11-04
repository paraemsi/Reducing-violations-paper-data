#include "parallel_letter_frequency.h"
#include <array>
#include <cctype>
#include <thread>
#include <algorithm>

namespace parallel_letter_frequency {

frequency_map letter_frequency(const std::vector<std::string>& texts)
{
    if (texts.empty()) {
        return {};
    }

    unsigned int n_threads = std::thread::hardware_concurrency();
    if (n_threads == 0) {
        n_threads = 2;                    // sensible fallback
    }
    n_threads = std::min<unsigned int>(n_threads, texts.size());

    std::vector<std::array<int, 26>> partials(n_threads);
    for (auto& arr : partials) {
        arr.fill(0);
    }

    auto worker = [&](size_t begin, size_t end, size_t idx) {
        auto& local = partials[idx];
        for (size_t i = begin; i < end; ++i) {
            for (char ch : texts[i]) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = static_cast<char>(
                        std::tolower(static_cast<unsigned char>(ch)));
                    if (lower >= 'a' && lower <= 'z') {
                        local[lower - 'a']++;
                    }
                }
            }
        }
    };

    std::vector<std::thread> workers;
    size_t base_block = texts.size() / n_threads;
    size_t extras     = texts.size() % n_threads;

    size_t begin = 0;
    for (size_t i = 0; i < n_threads; ++i) {
        size_t end = begin + base_block + (i < extras ? 1 : 0);
        workers.emplace_back(worker, begin, end, i);
        begin = end;
    }

    for (auto& t : workers) {
        t.join();
    }

    std::array<int, 26> totals{};
    totals.fill(0);
    for (const auto& local : partials) {
        for (size_t i = 0; i < 26; ++i) {
            totals[i] += local[i];
        }
    }

    frequency_map result;
    for (size_t i = 0; i < 26; ++i) {
        if (totals[i] > 0) {
            result[static_cast<char>('a' + i)] = totals[i];
        }
    }
    return result;
}

frequency_map frequency(const std::vector<std::string>& texts)
{
    return letter_frequency(texts);
}

}
