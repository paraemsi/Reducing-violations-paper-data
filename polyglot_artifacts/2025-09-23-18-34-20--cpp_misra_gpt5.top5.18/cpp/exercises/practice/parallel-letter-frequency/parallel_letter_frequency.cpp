#include "parallel_letter_frequency.h"

#include <cstddef>
#include <cctype>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {

auto count_letters(std::string_view text) -> frequency_map
{
    frequency_map freq{};

    for (const char_type ch : text) {
        using traits = std::char_traits<char_type>;
        const unsigned char uch = static_cast<unsigned char>(ch);

        if (std::isalpha(static_cast<int>(uch)) != 0) {
            const int lower_i = std::tolower(static_cast<int>(uch));
            const char_type lower = traits::to_char_type(static_cast<typename traits::int_type>(lower_i));
            ++freq[lower];
        }
    }

    return freq;
}

}  // namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::size_t total = texts.size();

    if (total == static_cast<std::size_t>(0U)) {
        return frequency_map{};
    }

    const std::size_t hw = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t threads = (hw == static_cast<std::size_t>(0U)) ? static_cast<std::size_t>(1U) : hw;
    const std::size_t tcount = (threads < total) ? threads : total;
    const std::size_t chunk = ((total + (tcount - static_cast<std::size_t>(1U))) / tcount);

    std::vector<frequency_map> partials(tcount);
    std::vector<std::thread> workers{};
    workers.reserve(tcount);

    for (std::size_t t = static_cast<std::size_t>(0U); t < tcount; ++t) {
        const std::size_t start = (t * chunk);
        const std::size_t end = (((start + chunk) < total) ? (start + chunk) : total);

        workers.emplace_back([&texts, &partials, t, start, end]() {
            frequency_map local{};
            for (std::size_t i = start; i < end; ++i) {
                const frequency_map counts = count_letters(texts[i]);
                for (const auto& kv : counts) {
                    local[kv.first] = (local[kv.first] + kv.second);
                }
            }
            partials[t] = std::move(local);
        });
    }

    for (auto& th : workers) {
        th.join();
    }

    frequency_map result{};
    for (const auto& part : partials) {
        for (const auto& kv : part) {
            result[kv.first] = (result[kv.first] + kv.second);
        }
    }

    return result;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());
    for (const std::string& s : texts) {
        views.emplace_back(std::string_view{s});
    }
    return frequency(views);
}

}  // namespace parallel_letter_frequency
