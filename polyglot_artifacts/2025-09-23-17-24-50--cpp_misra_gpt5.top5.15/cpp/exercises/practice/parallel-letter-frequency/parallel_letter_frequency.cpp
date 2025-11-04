#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

result_map frequency(const std::vector<std::string_view>& texts)
{
    // Decide the number of worker threads: at least 1, no more than texts.size()
    const auto hw = std::thread::hardware_concurrency();
    const std::size_t suggested = (hw == 0U) ? static_cast<std::size_t>(1U) : static_cast<std::size_t>(hw);
    const std::size_t thread_count = std::max<std::size_t>(static_cast<std::size_t>(1U),
        std::min<std::size_t>(texts.size(), suggested));

    if (texts.empty()) {
        return result_map{};
    }

    // Prepare per-thread partial results
    std::vector<result_map> partials(thread_count);

    // Compute chunk sizes
    const std::size_t total = texts.size();
    const std::size_t chunk = (total + (thread_count - static_cast<std::size_t>(1U))) / thread_count;

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (std::size_t t = 0U; t < thread_count; ++t) {
        const std::size_t start = (t * chunk);
        const std::size_t end = std::min<std::size_t>(total, (start + chunk));

        threads.emplace_back([start, end, &texts, &partials, t]() {
            result_map local{};
            for (std::size_t i = start; i < end; ++i) {
                const std::string_view s = texts[i];
                for (const char ch : s) {
                    using traits = std::char_traits<char>;
                    const traits::int_type ich = traits::to_int_type(ch);
                    if (std::isalpha(ich) != 0) {
                        const traits::char_type lower = traits::to_char_type(std::tolower(ich));
                        // Increment the count for this character
                        local[lower] = static_cast<count_t>(local[lower] + static_cast<count_t>(1U));
                    }
                }
            }
            // Store local result in this thread's slot (unique index -> no synchronization needed)
            partials[t] = std::move(local);
        });
    }

    for (std::thread& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    // Merge partial results
    result_map result{};
    for (const result_map& part : partials) {
        for (const auto& kv : part) {
            const char key = kv.first;
            const count_t val = kv.second;
            result[key] = static_cast<count_t>(result[key] + val);
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
