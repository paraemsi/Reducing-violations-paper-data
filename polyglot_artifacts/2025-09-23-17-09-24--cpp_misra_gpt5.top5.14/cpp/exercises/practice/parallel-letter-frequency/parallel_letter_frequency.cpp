#include "parallel_letter_frequency.h"

#include <cstddef>
#include <functional>
#include <locale>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {

auto count_range_by_index(const std::vector<std::string_view>& texts,
                          const std::size_t start,
                          const std::size_t count,
                          const std::locale& loc) -> frequency_map
{
    frequency_map local{};

    for (std::size_t idx = start; idx < (start + count); ++idx) {
        const std::string_view& str = texts[idx];
        for (std::string_view::const_iterator it = str.begin(); it != str.end(); ++it) {
            const char ch = *it;
            if (std::isalpha(ch, loc)) {
                const char lower = std::tolower(ch, loc);
                const auto found = local.find(lower);
                if (found == local.end()) {
                    local.emplace(lower, static_cast<std::int32_t>(1));
                } else {
                    found->second = static_cast<std::int32_t>((found->second) + static_cast<std::int32_t>(1));
                }
            }
        }
    }

    return local;
}

void worker(const std::vector<std::string_view>& texts,
            const std::size_t start,
            const std::size_t count,
            std::locale loc,
            frequency_map* out)
{
    if (out != nullptr) {
        frequency_map local = count_range_by_index(texts, start, count, loc);
        *out = std::move(local);
    }
}

}  // namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    frequency_map result{};

    if (texts.empty()) {
        return result;
    }

    const std::locale loc{};

    std::size_t hw = static_cast<std::size_t>(std::thread::hardware_concurrency());
    if (hw == static_cast<std::size_t>(0U)) {
        hw = static_cast<std::size_t>(1U);
    }

    const std::size_t n_threads = ((texts.size() < hw) ? texts.size() : hw);

    if (n_threads <= static_cast<std::size_t>(1U)) {
        return count_range_by_index(texts, static_cast<std::size_t>(0U), texts.size(), loc);
    }

    std::vector<std::thread> threads{};
    threads.reserve(n_threads);

    std::vector<frequency_map> locals(n_threads);

    const std::size_t total = texts.size();
    const std::size_t base = (total / n_threads);
    const std::size_t rem = (total % n_threads);

    std::size_t start = static_cast<std::size_t>(0U);
    for (std::size_t i = static_cast<std::size_t>(0U); i < n_threads; ++i) {
        const std::size_t count = (base + ((i < rem) ? static_cast<std::size_t>(1U) : static_cast<std::size_t>(0U)));
        threads.emplace_back(worker, std::cref(texts), start, count, loc, &locals[i]);
        start = (start + count);
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    for (const frequency_map& local : locals) {
        for (const auto& kv : local) {
            const auto it = result.find(kv.first);
            if (it == result.end()) {
                result.emplace(kv.first, kv.second);
            } else {
                it->second = static_cast<std::int32_t>((it->second) + (kv.second));
            }
        }
    }

    return result;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());
    for (const std::string& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}  // namespace parallel_letter_frequency
