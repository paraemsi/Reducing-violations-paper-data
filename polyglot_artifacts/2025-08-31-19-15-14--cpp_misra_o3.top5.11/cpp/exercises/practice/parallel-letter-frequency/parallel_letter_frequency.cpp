#include "parallel_letter_frequency.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

    // Public interface must return `std::map<char, int>` as required by tests.
    std::map<char, int> frequency(const std::vector<std::string>& texts)
    {
        // Decide how many worker threads to use.
        std::size_t hw_threads = std::thread::hardware_concurrency();
        std::size_t thread_count = (hw_threads == 0U) ? 1U : hw_threads;
        thread_count = std::min(thread_count, texts.size());

        if (thread_count == 0U) {
            return {};
        }

        // Each thread updates its own local counter array.
        std::vector<std::array<std::uint32_t, 26U>> partial_counts(thread_count);
        for (auto& arr : partial_counts) {
            arr.fill(0U);
        }

        auto worker =
            [&partial_counts, &texts](std::size_t begin,
                                      std::size_t end,
                                      std::size_t slot) noexcept
        {
            auto& local = partial_counts[slot];

            for (std::size_t i = begin; i < end; ++i) {
                const std::string& str = texts[i];

                for (char ch : str) {
                    if (std::isalpha(static_cast<unsigned char>(ch)) != 0) {
                        char lower = static_cast<char>(
                            std::tolower(static_cast<unsigned char>(ch)));

                        std::size_t index = static_cast<std::size_t>(
                            std::char_traits<char>::to_int_type(lower)
                            - std::char_traits<char>::to_int_type('a'));

                        local[index] += 1U;
                    }
                }
            }
        };

        // Launch threads, distributing texts as evenly as possible.
        std::vector<std::thread> threads;
        threads.reserve(thread_count);

        std::size_t block_size = texts.size() / thread_count;
        std::size_t remainder  = texts.size() % thread_count;

        std::size_t begin = 0U;
        for (std::size_t t = 0U; t < thread_count; ++t) {
            std::size_t end = begin + block_size + ((t < remainder) ? 1U : 0U);
            threads.emplace_back(worker, begin, end, t);
            begin = end;
        }

        for (auto& th : threads) {
            th.join();
        }

        // Combine the partial results.
        std::array<std::uint32_t, 26U> global_counts {};
        global_counts.fill(0U);

        for (const auto& arr : partial_counts) {
            for (std::size_t i = 0U; i < 26U; ++i) {
                global_counts[i] += arr[i];
            }
        }

        // Build the resulting map.
        std::map<char, int> result {};
        for (std::size_t i = 0U; i < 26U; ++i) {
            if (global_counts[i] > 0U) {
                char letter = static_cast<char>(
                    std::char_traits<char>::to_int_type('a')
                    + static_cast<int>(i));
                // Cast is safe: counts never exceed `int` range in tests.
                result.insert({ letter, static_cast<int>(global_counts[i]) });
            }
        }

        return result;
    }

}   // namespace parallel_letter_frequency
