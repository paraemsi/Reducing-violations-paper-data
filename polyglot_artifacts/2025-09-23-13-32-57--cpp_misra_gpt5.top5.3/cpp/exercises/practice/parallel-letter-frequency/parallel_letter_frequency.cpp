#include "parallel_letter_frequency.h"

#include <algorithm>
#include <locale>
#include <string_view>
#include <thread>

namespace {

// Count letters in a range of strings [first, last)
parallel_letter_frequency::frequency_map count_range(
    std::vector<std::string_view>::const_iterator first,
    std::vector<std::string_view>::const_iterator last) {
    const std::locale loc{};
    parallel_letter_frequency::frequency_map local_counts{};

    for (auto it = first; it != last; ++it) {
        std::string_view text = *it;
        for (const char ch : text) {
            if (std::isalpha(ch, loc)) {
                const char lowered = std::tolower(ch, loc);
                // Increment count for lowered letter
                ++(local_counts[lowered]);
            }
        }
    }
    return local_counts;
}

}  // unnamed namespace

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return frequency_map{};
    }

    const std::uint32_t hc = std::thread::hardware_concurrency();
    const std::size_t hw_threads =
        static_cast<std::size_t>(((hc > static_cast<std::uint32_t>(0U)) ? hc : static_cast<std::uint32_t>(2U)));

    const std::size_t threads_count = (std::min)(texts.size(), hw_threads);

    const std::size_t block_size =
        (((texts.size()) + (threads_count)) - static_cast<std::size_t>(1U)) / (threads_count);

    std::vector<frequency_map> partials(threads_count);
    std::vector<std::thread> workers{};
    workers.reserve(threads_count);

    for (std::size_t i = 0U; i < threads_count; ++i) {
        const std::size_t start_index = (i * block_size);
        const std::size_t end_index =
            (std::min)((start_index + block_size), texts.size());

        auto first = texts.cbegin() + static_cast<std::vector<std::string_view>::difference_type>(start_index);
        auto last  = texts.cbegin() + static_cast<std::vector<std::string_view>::difference_type>(end_index);

        workers.emplace_back([first, last, &partials, i]() {
            partials[i] = count_range(first, last);
        });
    }

    for (std::thread& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    frequency_map result{};

    for (const frequency_map& part : partials) {
        for (const auto& kv : part) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
