#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cstddef>
#include <locale>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {

// Count letters in a single text segment into the provided map.
// Uses the C "classic" locale to restrict classification to ASCII letters.
inline void accumulate_text(std::string_view text, frequency_map& out) {
    const std::locale loc = std::locale::classic();

    for (const char c : text) {
        if (std::isalpha(c, loc) != 0) {
            const char lower = std::tolower(c, loc);
            out[lower] = static_cast<count_t>(out[lower] + static_cast<count_t>(1U));
        } else {
            // no-op
        }
    }
}

}  // namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map {
    if ((texts.empty())) {
        return {};
    }

    const std::size_t hw = static_cast<std::size_t>(std::thread::hardware_concurrency());
    std::size_t thread_count = (hw != static_cast<std::size_t>(0U)) ? hw : static_cast<std::size_t>(1U);
    thread_count = (std::min(texts.size(), thread_count));

    if ((thread_count < static_cast<std::size_t>(1U))) {
        thread_count = static_cast<std::size_t>(1U);
    } else {
        // no-op
    }

    const std::size_t n = texts.size();
    const std::size_t chunk = (n + (thread_count - static_cast<std::size_t>(1U))) / thread_count;

    std::vector<frequency_map> partials;
    partials.resize(thread_count);

    std::vector<std::thread> workers;
    workers.reserve(thread_count);

    for (std::size_t i = static_cast<std::size_t>(0U); (i < thread_count); ++i) {
        const std::size_t start = (i * chunk);
        const std::size_t end = (std::min(n, (start + chunk)));

        if ((start >= end)) {
            break;
        } else {
            // no-op
        }

        workers.emplace_back([&texts, start, end, &partials, i]() {
            frequency_map local;
            for (std::size_t idx = start; (idx < end); ++idx) {
                accumulate_text(texts[idx], local);
            }
            partials[i] = std::move(local);
        });
    }

    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        } else {
            // no-op
        }
    }

    frequency_map result;
    for (const auto& part : partials) {
        for (const auto& kv : part) {
            result[kv.first] = static_cast<count_t>(result[kv.first] + kv.second);
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
