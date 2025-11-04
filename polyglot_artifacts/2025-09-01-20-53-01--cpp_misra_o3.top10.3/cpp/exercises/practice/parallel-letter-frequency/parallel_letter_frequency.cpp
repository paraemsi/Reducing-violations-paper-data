#include "parallel_letter_frequency.h"

#include <thread>
#include <locale>
#include <string_view>
#include <vector>
#include <algorithm>

namespace parallel_letter_frequency {

[[nodiscard]] auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    frequency_map total{};

    const std::size_t det_threads =
        static_cast<std::size_t>(std::thread::hardware_concurrency());

    const std::size_t fallback_threads = static_cast<std::size_t>(2U);

    const std::size_t wanted_threads =
        (det_threads != static_cast<std::size_t>(0U))
            ? det_threads
            : fallback_threads;

    const std::size_t num_threads =
        std::min(wanted_threads,
                 (texts.empty() ? static_cast<std::size_t>(1U)
                                : texts.size()));

    if (texts.empty()) {
        return total;
    }

    const std::size_t chunk_size =
        ( (texts.size() + (num_threads - static_cast<std::size_t>(1U))) )
        / num_threads;

    std::vector<std::thread>       workers{};
    std::vector<frequency_map>     partial(num_threads);

    auto worker =
        [&texts](frequency_map& dest, std::size_t begin, std::size_t end) {
            const std::locale loc{};
            for (std::size_t idx = begin; idx < end; ++idx) {
                for (char ch : texts[idx]) {
                    if (std::isalpha(static_cast<unsigned char>(ch), loc) != 0) {
                        const char lower =
                            std::tolower(static_cast<unsigned char>(ch), loc);
                        ++dest[lower];
                    }
                }
            }
        };

    std::size_t begin = static_cast<std::size_t>(0U);
    for (std::size_t i = static_cast<std::size_t>(0U); i < num_threads; ++i) {
        const std::size_t end =
            std::min(static_cast<std::size_t>(texts.size()),
                     begin + chunk_size);
        workers.emplace_back(worker, std::ref(partial[i]), begin, end);
        begin = end;
    }

    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    for (const auto& part : partial) {
        for (const auto& p : part) {
            total[p.first] += p.second;
        }
    }

    return total;
}

[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    std::vector<std::string> copy{};
    copy.reserve(texts.size());
    for (const auto sv : texts) {
        copy.emplace_back(std::string{sv});
    }
    return frequency(copy);
}

} // namespace parallel_letter_frequency
