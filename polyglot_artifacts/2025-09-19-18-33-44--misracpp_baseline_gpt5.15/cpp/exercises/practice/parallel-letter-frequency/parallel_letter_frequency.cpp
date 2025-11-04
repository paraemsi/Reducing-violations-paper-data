#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <string>
#include <string_view>
#include <thread>
#include <map>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

frequency_map frequency(const std::vector<std::string_view>& texts) {
    frequency_map total;

    if (texts.empty()) {
        return total;
    }

    unsigned int hc = std::thread::hardware_concurrency();
    if (hc == 0) hc = 2;
    std::size_t thread_count = std::min<std::size_t>(texts.size(), hc);

    std::vector<std::future<frequency_map>> futures;
    futures.reserve(thread_count);

    auto worker = [&texts](std::size_t begin, std::size_t end) -> frequency_map {
        frequency_map local;
        for (std::size_t i = begin; i < end; ++i) {
            std::string_view s = texts[i];
            for (char ch : s) {
                unsigned char uc = static_cast<unsigned char>(ch);
                char lc = static_cast<char>(std::tolower(uc));
                if (lc >= 'a' && lc <= 'z') {
                    ++local[lc];
                }
            }
        }
        return local;
    };

    std::size_t chunk = texts.size() / thread_count;
    std::size_t rem = texts.size() % thread_count;
    std::size_t start = 0;
    for (std::size_t t = 0; t < thread_count; ++t) {
        std::size_t count = chunk + (t < rem ? 1 : 0);
        std::size_t end = start + count;
        futures.emplace_back(std::async(std::launch::async, worker, start, end));
        start = end;
    }

    for (auto& fut : futures) {
        frequency_map part = fut.get();
        for (const auto& kv : part) {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

}  // namespace parallel_letter_frequency
