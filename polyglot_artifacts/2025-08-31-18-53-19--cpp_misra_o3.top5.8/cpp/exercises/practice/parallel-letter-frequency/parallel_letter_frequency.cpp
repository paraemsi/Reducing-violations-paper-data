#include "parallel_letter_frequency.h"

#include <locale>
#include <cctype>
#include <mutex>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    frequency_map result {};
    std::mutex result_mutex {};
    std::vector<std::thread> workers {};
    workers.reserve(texts.size());

    for (std::string_view text : texts) {
        workers.emplace_back(
            [&result, &result_mutex, text]() {
                frequency_map local {};
                const std::locale loc {};

                for (char ch : text) {
                    const unsigned char uchar { static_cast<unsigned char>(ch) };
                    if ((std::isalpha(uchar, loc) != 0)) {
                        const char lower_ch { static_cast<char>(std::tolower(uchar, loc)) };
                        ++local[lower_ch];
                    }
                }

                {
                    std::scoped_lock<std::mutex> lock { result_mutex };
                    for (const auto& elem : local) {
                        result[elem.first] += elem.second;
                    }
                }
            });
    }

    for (std::thread& t : workers) {
        t.join();
    }

    return result;
}

}  /* namespace parallel_letter_frequency */
