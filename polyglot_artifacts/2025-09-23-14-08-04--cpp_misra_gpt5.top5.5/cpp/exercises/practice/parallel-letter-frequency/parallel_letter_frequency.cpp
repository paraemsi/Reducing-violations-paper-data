#include "parallel_letter_frequency.h"

#include <cctype>
#include <future>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {
/* Count letters in a single text (case-insensitive). */
auto count_letters_in_text(const std::string& text) -> frequency_map
{
    frequency_map counts{};

    for (const char ch : text) {
        const unsigned char uch = static_cast<unsigned char>(ch);
        const std::char_traits<unsigned char>::int_type ch_int =
            std::char_traits<unsigned char>::to_int_type(uch);

        if ((std::isalpha(ch_int) != 0)) {
            const std::char_traits<unsigned char>::int_type lowered_int = std::tolower(ch_int);
            const unsigned char lower_uch =
                std::char_traits<unsigned char>::to_char_type(lowered_int);
            const char lower_ch = static_cast<char>(lower_uch);
            ++counts[lower_ch];
        } else {
            /* not a letter - ignore */
        }
    }

    return counts;
}
}  // namespace

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    for (const std::string& t : texts) {
        tasks.emplace_back(std::async(std::launch::async, &count_letters_in_text, t));
    }

    frequency_map total{};
    for (auto& fut : tasks) {
        frequency_map local = fut.get();
        for (const auto& kv : local) {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

}  // namespace parallel_letter_frequency
