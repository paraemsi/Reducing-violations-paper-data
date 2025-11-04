#include "parallel_letter_frequency.h"

#include <atomic>
#include <cstddef>
#include <locale>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const std::string& s : texts) {
        views.emplace_back(std::string_view(s));
    }
    return frequency(views);
}

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::locale loc = std::locale::classic();

    std::size_t number_of_threads = texts.size();
    const auto hc = std::thread::hardware_concurrency();
    if ((hc != 0U)) {
        const std::size_t hc_sz = static_cast<std::size_t>(hc);
        if ((hc_sz < number_of_threads)) {
            number_of_threads = hc_sz;
        }
    }

    if ((number_of_threads == static_cast<std::size_t>(0U))) {
        return frequency_map{};
    }

    std::vector<frequency_map> partials(number_of_threads);
    std::atomic<std::size_t> next_index{static_cast<std::size_t>(0U)};
    std::vector<std::thread> workers;
    workers.reserve(number_of_threads);

    for (std::size_t t = static_cast<std::size_t>(0U); (t < number_of_threads); ++t) {
        workers.emplace_back([&texts, &partials, &next_index, t, loc]() {
            frequency_map& local = partials[t];
            for (;;) {
                const std::size_t idx = next_index.fetch_add(static_cast<std::size_t>(1U), std::memory_order_relaxed);
                if ((idx >= texts.size())) {
                    break;
                }
                const std::string_view s = texts[idx];
                for (const char ch : s) {
                    if (std::isalpha(ch, loc)) {
                        const char lower = std::tolower(ch, loc);
                        if ((std::string_view("abcdefghijklmnopqrstuvwxyz").find(lower) != std::string_view::npos)) {
                            ++(local[lower]);
                        }
                    }
                }
            }
        });
    }

    for (auto& th : workers) {
        th.join();
    }

    frequency_map result{};
    for (const auto& local : partials) {
        for (const auto& kv : local) {
            result[kv.first] = ((result[kv.first]) + kv.second);
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
