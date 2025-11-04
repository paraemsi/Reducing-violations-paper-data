#include "parallel_letter_frequency.h"

#include <cstddef>
#include <locale>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::size_t total = texts.size();
    if (total == static_cast<std::size_t>(0U)) {
        return frequency_map{};
    }

    std::size_t hardware = static_cast<std::size_t>(std::thread::hardware_concurrency());
    if (hardware == static_cast<std::size_t>(0U)) {
        hardware = static_cast<std::size_t>(2U);
    }

    const std::size_t num_workers = (hardware < total) ? hardware : total;
    const std::size_t block_size = (num_workers != static_cast<std::size_t>(0U))
        ? ((total + (num_workers - static_cast<std::size_t>(1U))) / num_workers)
        : total;

    std::vector<frequency_map> partials(num_workers);
    std::vector<std::thread> threads;
    threads.reserve(num_workers);

    for (std::size_t i = static_cast<std::size_t>(0U); (i < num_workers); ++i) {
        const std::size_t start = (i * block_size);
        if (start >= total) {
            break;
        }
        const std::size_t end = ((start + block_size) < total) ? (start + block_size) : total;

        threads.emplace_back(
            [&texts, &partials, i, start, end]() {
                frequency_map local{};
                const std::locale loc{};
                for (std::size_t idx = start; (idx < end); ++idx) {
                    const std::string_view s = texts[idx];
                    for (const char ch : s) {
                        if (std::isalpha(ch, loc)) {
                            const char lowered = std::tolower(ch, loc);
                            ++(local[lowered]);
                        }
                    }
                }
                partials[i] = std::move(local);
            }
        );
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    frequency_map result{};
    for (const auto& part : partials) {
        for (const auto& kv : part) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
