#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstddef>
#include <mutex>
#include <string_view>
#include <thread>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string>& texts)
{
    frequency_map global_freq {};

    if (texts.empty()) {
        return global_freq;
    }

    const std::size_t detected_threads =
        static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t worker_count =
        (detected_threads == static_cast<std::size_t>(0)) ? static_cast<std::size_t>(1) : detected_threads;

    const std::size_t total_texts = texts.size();
    const std::size_t chunk_size =
        ((total_texts + worker_count) - static_cast<std::size_t>(1)) / worker_count;

    std::mutex merge_mutex {};
    std::vector<std::thread> workers {};
    workers.reserve(worker_count);

    auto worker = [&texts, &merge_mutex, &global_freq]
                  (std::size_t begin, std::size_t end) {
        frequency_map local_freq {};

        for (std::size_t idx = begin; (idx < end); ++idx) {
            const std::string& str = texts.at(idx);

            for (char ch : str) {
                const int int_ch { std::char_traits<char>::to_int_type(ch) };

                if (std::isalpha(int_ch) != 0) {
                    const int lower_int { std::tolower(int_ch) };
                    const char lower_ch { std::char_traits<char>::to_char_type(lower_int) };
                    ++local_freq[lower_ch];
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock { merge_mutex };
            for (const auto& kv : local_freq) {
                global_freq[kv.first] += kv.second;
            }
        }
    };

    std::size_t start = static_cast<std::size_t>(0);
    while (start < total_texts) {
        const std::size_t end =
            ((start + chunk_size) < total_texts) ? (start + chunk_size)
                                                 : total_texts;
        workers.emplace_back(worker, start, end);
        start = end;
    }

    for (std::thread& thr : workers) {
        if (thr.joinable()) {
            thr.join();
        }
    }

    return global_freq;
}

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    std::vector<std::string> copied {};
    copied.reserve(texts.size());

    for (const std::string_view sv : texts) {
        copied.emplace_back(sv);
    }

    return frequency(copied);
}

} // namespace parallel_letter_frequency
