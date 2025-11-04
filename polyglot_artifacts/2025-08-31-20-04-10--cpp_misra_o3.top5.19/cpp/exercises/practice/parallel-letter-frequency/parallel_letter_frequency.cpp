#include "parallel_letter_frequency.h"

#include <thread>
#include <future>
#include <array>
#include <locale>
#include <cstddef>   /* for std::size_t */
#include <string_view>

namespace parallel_letter_frequency {

namespace {

/* lower-case English alphabet – used for classification without relying
 * on the numeric value of any character */
constexpr char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
constexpr std::size_t alphabet_length = 26U;
constexpr std::string_view letters(alphabet, alphabet_length);

} // unnamed namespace


frequency_map frequency(const std::vector<std::string_view>& texts)
{
    const std::size_t text_count = texts.size();
    if (text_count == 0U) {
        return frequency_map{};
    }

    std::size_t max_threads = std::thread::hardware_concurrency();
    if (max_threads == 0U) {
        max_threads = 1U;
    }

    const std::size_t thread_count = (text_count < max_threads) ? text_count : max_threads;
    const std::size_t chunk_size =
        ((text_count + thread_count) - 1U) / thread_count;   /* ceiling division */

    std::vector<
        std::future<std::array<count_type, alphabet_length>>> futures;
    futures.reserve(thread_count);

    for (std::size_t i = 0U; i < thread_count; ++i) {
        const std::size_t begin_index = i * chunk_size;
        const std::size_t end_index =
            ((begin_index + chunk_size) < text_count)
                ? (begin_index + chunk_size)
                : text_count;

        futures.emplace_back(std::async(
            std::launch::async,
            [begin_index, end_index, &texts]() {
                std::array<count_type, alphabet_length> local_counts{};
                local_counts.fill(0U);

                const std::locale loc{};
                for (std::size_t idx = begin_index; idx < end_index; ++idx) {
                    const std::string_view text = texts[idx];
                    for (char raw_ch : text) {
                        char lower_ch = std::tolower(raw_ch, loc);

                        const std::string_view::size_type position =
                            letters.find(lower_ch);

                        if (position != std::string::npos) {
                            ++local_counts[position];
                        }
                    }
                }

                return local_counts;
            }));
    }

    std::array<count_type, alphabet_length> total_counts{};
    total_counts.fill(0U);

    for (auto& fut : futures) {
        const std::array<count_type, alphabet_length> local = fut.get();
        for (std::size_t idx = 0U; idx < alphabet_length; ++idx) {
            total_counts[idx] = total_counts[idx] + local[idx];
        }
    }

    frequency_map result{};
    for (std::size_t idx = 0U; idx < alphabet_length; ++idx) {
        if (total_counts[idx] != 0U) {
            result.insert({alphabet[idx], total_counts[idx]});
        }
    }

    return result;
}

} // namespace parallel_letter_frequency
