#include "parallel_letter_frequency.h"

#include <array>
#include <locale>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

namespace
{
/*  Helper constant: explicit list of lower-case ASCII letters.
 *  Avoids any arithmetic on character values (MISRA compliance).
 */
constexpr std::array<char, 26U> letters{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
}   // unnamed namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    /*  Decide how many worker threads we are going to start.                 */
    const std::uint32_t hardware_threads{
        (std::thread::hardware_concurrency() == 0U)
            ? 2U
            : std::thread::hardware_concurrency()};
    const std::size_t worker_count{
        (texts.size() < static_cast<std::size_t>(hardware_threads))
            ? texts.size()
            : static_cast<std::size_t>(hardware_threads)};

    /*  Each worker fills its own local counter array, avoiding any sharing
     *  during the actual counting phase.                                     */
    std::vector<std::array<std::uint32_t, 26U>> partial_counts(
        worker_count, std::array<std::uint32_t, 26U>{});

    std::vector<std::thread> workers{};
    workers.reserve(worker_count);

    const std::size_t chunk_size{
        (worker_count == 0U) ? 0U
                             : ((texts.size() + (worker_count - 1U)) /
                                worker_count)};

    for (std::size_t idx{0U}; idx < worker_count; ++idx)
    {
        const std::size_t begin{idx * chunk_size};
        const std::size_t end{
            ((begin + chunk_size) > texts.size()) ? texts.size()
                                                  : (begin + chunk_size)};

        workers.emplace_back(
            [begin, end, &texts, &partial_counts, idx]() {
                std::locale loc{};
                auto& local_counter{partial_counts[idx]};

                for (std::size_t i{begin}; i < end; ++i)
                {
                    for (const char ch_raw : texts[i])
                    {
                        if (std::isalpha(static_cast<unsigned char>(ch_raw),
                                         loc))
                        {
                            const char ch_lower{
                                std::tolower(ch_raw, loc)};
                            /* Find the position inside our letters array     */
                            for (std::size_t pos{0U}; pos < letters.size();
                                 ++pos)
                            {
                                if (ch_lower == letters[pos])
                                {
                                    ++local_counter[pos];
                                    break;
                                }
                            }
                        }
                    }
                }
            });
    }

    for (auto& th : workers)
    {
        th.join();
    }

    /*  Merge the partial results                                             */
    std::array<std::uint32_t, 26U> total_counts{};
    for (const auto& part : partial_counts)
    {
        for (std::size_t i{0U}; i < letters.size(); ++i)
        {
            total_counts[i] += part[i];
        }
    }

    frequency_map result{};
    for (std::size_t i{0U}; i < letters.size(); ++i)
    {
        if (total_counts[i] != 0U)
        {
            result.emplace(letters[i], total_counts[i]);
        }
    }

    return result;
}

/*  Wrapper that accepts std::string inputs and forwards the work to the
 *  std::string_view implementation to satisfy legacy test-suites.
 */
auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());
    for (const std::string& s : texts)
    {
        views.emplace_back(s);
    }

    return frequency(views);
}

}   // namespace parallel_letter_frequency
