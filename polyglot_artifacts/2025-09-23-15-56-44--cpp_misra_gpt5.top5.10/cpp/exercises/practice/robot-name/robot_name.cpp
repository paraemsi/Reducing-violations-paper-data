#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    // Allowed character sets (selected by index; no arithmetic on character values)
    static constexpr char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr char DIGITS[] = "0123456789";

    // Registry of allocated names
    std::unordered_set<std::string> used_names{};
    std::mutex used_names_mutex{};

    std::string make_random_name()
    {
        // Independent PRNG per call to avoid shared-state data races
        std::random_device rd{};
        std::mt19937 gen{ rd() };

        std::uniform_int_distribution<std::uint32_t> dist_letter{
            static_cast<std::uint32_t>(0U), static_cast<std::uint32_t>(25U)
        };
        std::uniform_int_distribution<std::uint32_t> dist_digit{
            static_cast<std::uint32_t>(0U), static_cast<std::uint32_t>(9U)
        };

        const char l0 = LETTERS[static_cast<std::size_t>(dist_letter(gen))];
        const char l1 = LETTERS[static_cast<std::size_t>(dist_letter(gen))];
        const char d0 = DIGITS[static_cast<std::size_t>(dist_digit(gen))];
        const char d1 = DIGITS[static_cast<std::size_t>(dist_digit(gen))];
        const char d2 = DIGITS[static_cast<std::size_t>(dist_digit(gen))];

        std::string out{};
        out.reserve(static_cast<std::size_t>(5U));
        out.push_back(l0);
        out.push_back(l1);
        out.push_back(d0);
        out.push_back(d1);
        out.push_back(d2);
        return out;
    }

    std::string acquire_unique_name()
    {
        for (;;)
        {
            std::string candidate = make_random_name();

            {
                std::lock_guard<std::mutex> lock{ used_names_mutex };
                const auto insert_result = used_names.insert(candidate);
                if ((insert_result.second) != false)
                {
                    return *(insert_result.first);
                }
            }
        }
    }
}  // namespace

robot::robot()
    : current_name_{ acquire_unique_name() }
{
}

std::string robot::name() const
{
    return current_name_;
}

void robot::reset()
{
    {
        std::lock_guard<std::mutex> lock{ used_names_mutex };
        (void)used_names.erase(current_name_);
    }
    current_name_ = acquire_unique_name();
}

}  // namespace robot_name
