#include "parallel_letter_frequency.h"

#include <thread>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    const std::size_t n = texts.size();
    if (n == 0) {
        return {};
    }

    const unsigned hw = std::thread::hardware_concurrency();
    std::size_t workers = hw ? static_cast<std::size_t>(hw) : 2u;
    if (workers > n) {
        workers = n;
    }

    std::vector<frequency_map> locals(workers);
    std::vector<std::thread> threads;
    threads.reserve(workers);

    const std::size_t block_size = n / workers;
    const std::size_t remainder = n % workers;

    std::size_t begin = 0;
    for (std::size_t i = 0; i < workers; ++i) {
        const std::size_t end = begin + block_size + (i < remainder ? 1 : 0);
        threads.emplace_back([begin, end, &texts, &locals, i]() {
            auto& local = locals[i];
            for (std::size_t idx = begin; idx < end; ++idx) {
                std::string_view s = texts[idx];
                for (unsigned char ch : s) {
                    if (ch >= 'A' && ch <= 'Z') {
                        ++local[static_cast<char>(ch + ('a' - 'A'))];
                    } else if (ch >= 'a' && ch <= 'z') {
                        ++local[static_cast<char>(ch)];
                    }
                }
            }
        });
        begin = end;
    }

    for (auto& t : threads) {
        t.join();
    }

    frequency_map result;
    for (const auto& local : locals) {
        for (const auto& kv : local) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

frequency_map frequency(std::initializer_list<std::string_view> texts) {
    std::vector<std::string_view> views(texts.begin(), texts.end());
    return frequency(views);
}

}
