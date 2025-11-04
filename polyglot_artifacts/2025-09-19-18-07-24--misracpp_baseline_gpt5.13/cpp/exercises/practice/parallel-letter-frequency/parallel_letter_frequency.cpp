#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cstddef>
#include <map>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

namespace {
inline bool is_ascii_alpha(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

inline char to_lower_ascii(unsigned char c) {
    return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : static_cast<char>(c);
}

void count_range(const std::vector<std::string_view>& texts,
                 std::size_t begin,
                 std::size_t end,
                 frequency_map& out) {
    for (std::size_t i = begin; i < end; ++i) {
        for (unsigned char uc : texts[i]) {
            if (is_ascii_alpha(uc)) {
                char lc = to_lower_ascii(uc);
                ++out[lc];
            }
        }
    }
}
}  // namespace

[[nodiscard]] frequency_map frequency(const std::vector<std::string_view>& texts) {
    frequency_map total;

    if (texts.empty()) {
        return total;
    }

    unsigned int hc = std::thread::hardware_concurrency();
    std::size_t nthreads = static_cast<std::size_t>(hc == 0 ? 2 : hc);
    nthreads = std::min<std::size_t>(nthreads, texts.size());

    if (nthreads <= 1) {
        count_range(texts, 0, texts.size(), total);
        return total;
    }

    std::vector<frequency_map> partials(nthreads);
    std::vector<std::thread> threads;
    threads.reserve(nthreads);

    std::size_t base = texts.size() / nthreads;
    std::size_t extra = texts.size() % nthreads;

    std::size_t begin = 0;
    for (std::size_t i = 0; i < nthreads; ++i) {
        std::size_t count = base + (i < extra ? 1 : 0);
        std::size_t end = begin + count;

        threads.emplace_back([&texts, begin, end, &partials, i]() {
            count_range(texts, begin, end, partials[i]);
        });

        begin = end;
    }

    for (auto& t : threads) {
        t.join();
    }

    for (auto& part : partials) {
        for (const auto& kv : part) {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

[[nodiscard]] frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}  // namespace parallel_letter_frequency
