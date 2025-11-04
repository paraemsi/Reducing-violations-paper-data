#include "parallel_letter_frequency.h"

#include <array>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

namespace {
std::size_t choose_thread_count(std::size_t requested, std::size_t tasks) {
    if (tasks == 0) {
        return 1u;
    }
    if (requested == 0) {
        const auto hc = std::thread::hardware_concurrency();
        requested = hc ? static_cast<std::size_t>(hc) : 2u;
    }
    if (requested > tasks) {
        requested = tasks;
    }
    return requested ? requested : 1u;
}

inline void accumulate_text(std::string_view text, std::array<unsigned long long, 26>& counts) {
    for (unsigned char uc : text) {
        // Normalize to lowercase ASCII and count only 'a'..'z'
        if (uc >= 'A' && uc <= 'Z') {
            uc = static_cast<unsigned char>(uc - 'A' + 'a');
        }
        if (uc >= 'a' && uc <= 'z') {
            counts[uc - 'a']++;
        }
    }
}
}  // namespace



template <typename Texts>
frequency_map frequency_impl(const Texts& texts, std::size_t threads) {
    const std::size_t n_texts = texts.size();
    const std::size_t n_threads = choose_thread_count(threads, n_texts);

    if (n_texts == 0) {
        return {};
    }

    std::vector<std::array<unsigned long long, 26>> partial(n_threads);
    for (auto& arr : partial) {
        arr.fill(0);
    }

    std::vector<std::thread> workers;
    workers.reserve(n_threads);

    for (std::size_t t = 0; t < n_threads; ++t) {
        workers.emplace_back([t, n_threads, &texts, &partial]() {
            auto& local = partial[t];
            for (std::size_t i = t; i < texts.size(); i += n_threads) {
                accumulate_text(texts[i], local);
            }
        });
    }

    for (auto& th : workers) {
        th.join();
    }

    std::array<unsigned long long, 26> totals{};
    totals.fill(0);
    for (const auto& arr : partial) {
        for (std::size_t i = 0; i < 26; ++i) {
            totals[i] += arr[i];
        }
    }

    frequency_map result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (totals[i] > 0) {
            result[static_cast<char>('a' + static_cast<char>(i))] = static_cast<int>(totals[i]);
        }
    }

    return result;
}



frequency_map frequency(const std::vector<std::string_view>& texts, std::size_t threads) {
    return frequency_impl(texts, threads);
}

}  // namespace parallel_letter_frequency
