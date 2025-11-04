#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    const std::size_t n = texts.size();

    // One partial histogram per input text to avoid synchronization while counting.
    std::vector<std::array<int, 26>> partials(n);
    for (auto& arr : partials) {
        arr.fill(0);
    }

    // Spawn one worker per text. For typical Exercism inputs this is sufficient.
    std::vector<std::thread> workers;
    workers.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
        workers.emplace_back([&partials, &texts, i]() {
            auto& counts = partials[i];
            std::string_view s = texts[i];
            for (unsigned char uc : s) {
                if (std::isalpha(uc)) {
                    int idx = static_cast<int>(std::tolower(uc)) - 'a';
                    if (idx >= 0 && idx < 26) {
                        ++counts[static_cast<std::size_t>(idx)];
                    }
                }
            }
        });
    }

    for (auto& t : workers) {
        t.join();
    }

    // Reduce partial histograms into a single total.
    std::array<int, 26> total{};
    total.fill(0);
    for (const auto& arr : partials) {
        for (std::size_t k = 0; k < 26; ++k) {
            total[k] += arr[k];
        }
    }

    std::map<char, int> result;
    for (std::size_t k = 0; k < 26; ++k) {
        if (total[k] > 0) {
            result[static_cast<char>('a' + k)] = total[k];
        }
    }
    return result;
}

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}
