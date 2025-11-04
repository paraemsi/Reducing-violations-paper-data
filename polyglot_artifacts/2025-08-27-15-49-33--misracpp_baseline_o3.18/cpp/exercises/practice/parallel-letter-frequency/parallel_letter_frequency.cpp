#include "parallel_letter_frequency.h"
#include <thread>
#include <cctype>
#include <algorithm>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    // Short-circuit for empty input
    if (texts.empty()) {
        return {};
    }

    // Use at most hardware_concurrency threads and distribute the input
    // texts across them.  Falling back to one worker if the value cannot
    // be obtained.
    const std::size_t hw = std::thread::hardware_concurrency();
    const std::size_t num_workers = std::max<std::size_t>(1, hw == 0 ? 2 : hw);
    const std::size_t workers_to_start = std::min<std::size_t>(num_workers, texts.size());

    // Each worker produces its own local frequency map to avoid contention.
    std::vector<std::map<char, int>> partials(workers_to_start);
    std::vector<std::thread>          workers;
    workers.reserve(workers_to_start);

    for (std::size_t w = 0; w < workers_to_start; ++w) {
        workers.emplace_back([&, w]() {
            auto &local = partials[w];
            // Round-robin assignment of texts to workers ensures similar load
            for (std::size_t i = w; i < texts.size(); i += workers_to_start) {
                for (char ch : texts[i]) {
                    unsigned char u = static_cast<unsigned char>(ch);
                    if (std::isalpha(u)) {
                        local[static_cast<char>(std::tolower(u))]++;
                    }
                }
            }
        });
    }

    // Join all workers
    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Merge partial maps into the final result
    std::map<char, int> result;
    for (const auto& local : partials) {
        for (const auto& [letter, count] : local) {
            result[letter] += count;
        }
    }

    return result;
}

// Convenience overload: convert the vector of std::string to std::string_view
// and delegate to the main implementation above.  This makes the API usable
// with both std::string and std::string_view containers.
std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

} // namespace parallel_letter_frequency
