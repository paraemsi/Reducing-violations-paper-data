#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <thread>
#include <string_view>

namespace parallel_letter_frequency {

namespace {
inline void accumulate_text(frequency_map& local, std::string_view text) {
    for (unsigned char ch : text) {
        unsigned char lower = static_cast<unsigned char>(std::tolower(ch));
        if (lower >= 'a' && lower <= 'z') {
            ++local[static_cast<char>(lower)];
        }
    }
}
}  // namespace

frequency_map frequency(const std::vector<std::string>& texts, std::size_t workers) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views, workers);
}

frequency_map frequency(const std::vector<std::string_view>& texts, std::size_t workers) {
    std::size_t n_threads = workers;
    if (n_threads == 0) {
        n_threads = std::thread::hardware_concurrency();
    }
    if (n_threads == 0) {
        n_threads = 2;  // reasonable fallback if hardware_concurrency is unknown
    }
    if (texts.empty()) {
        return {};
    }
    if (n_threads > texts.size()) {
        n_threads = texts.size();
    }

    std::vector<frequency_map> partials(n_threads);
    std::vector<std::thread> threads;
    threads.reserve(n_threads);

    const std::size_t chunk = (texts.size() + n_threads - 1) / n_threads;

    for (std::size_t i = 0; i < n_threads; ++i) {
        const std::size_t start = i * chunk;
        if (start >= texts.size()) break;
        const std::size_t end = std::min(start + chunk, texts.size());

        threads.emplace_back([start, end, &texts, &partials, i]() {
            auto& local = partials[i];
            for (std::size_t idx = start; idx < end; ++idx) {
                accumulate_text(local, texts[idx]);
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    frequency_map result;
    for (const auto& local : partials) {
        for (const auto& kv : local) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

frequency_map count(const std::vector<std::string_view>& texts, std::size_t workers) {
    return frequency(texts, workers);
}

frequency_map count(const std::vector<std::string>& texts, std::size_t workers) {
    return frequency(texts, workers);
}



}  // namespace parallel_letter_frequency
