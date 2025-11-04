#include "parallel_letter_frequency.h"

#include <algorithm>
#include <locale>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    // Fast-path for empty input
    if (texts.empty()) {
        return {};
    }

    const std::size_t hwc_raw = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t hwc = ((hwc_raw != static_cast<std::size_t>(0U)) ? hwc_raw : static_cast<std::size_t>(2U));
    const std::size_t workers = std::min(texts.size(), hwc);

    // Prepare per-worker local frequency maps
    std::vector<frequency_map> locals(workers);

    // Chunking setup
    const std::size_t chunk = ((texts.size() + (workers - static_cast<std::size_t>(1U))) / workers);

    // Use classic "C" locale to ensure ASCII-like behavior for letter classification and case conversion
    const std::locale loc = std::locale::classic();

    // Launch worker threads
    std::vector<std::thread> threads;
    threads.reserve(workers);

    for (std::size_t w = static_cast<std::size_t>(0U); w < workers; ++w) {
        const std::size_t start = (w * chunk);
        const std::size_t end = std::min(texts.size(), (start + chunk));

        if (start < end) {
            threads.emplace_back([&texts, &locals, w, start, end, loc]() {
                frequency_map& local = locals[w];
                for (std::size_t i = start; i < end; ++i) {
                    const std::string_view s = texts[i];
                    for (const letter_t ch : s) {
                        if (std::isalpha(ch, loc)) {
                            const letter_t lower = std::tolower(ch, loc);
                            // Increment the count for this character
                            ++local[lower];
                        }
                    }
                }
            });
        } else {
            // Nothing to process in this worker
            threads.emplace_back([]() {
                // Intentionally empty
            });
        }
    }

    // Join all threads
    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Merge local maps into the final result
    frequency_map result;
    for (const frequency_map& local : locals) {
        for (const auto& kv : local) {
            // kv.second and result[kv.first] are std::uint32_t, safe to add
            result[kv.first] = (result[kv.first] + kv.second);
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
