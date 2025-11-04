#include "robot_name.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    std::unordered_set<std::string> g_used_names{};
    std::mutex g_mutex{};

    std::mt19937& prng()
    {
        thread_local std::mt19937 engine([]() {
            std::random_device rd{};
            std::seed_seq seed{
                rd(), rd(), rd(), rd(),
                rd(), rd(), rd(), rd()
            };
            return std::mt19937(seed);
        }());
        return engine;
    }

    std::string generate_name_impl(std::mt19937& engine)
    {
        static constexpr std::array<char, 26> letters = {
            'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
        };
        static constexpr std::array<char, 10> digits = {
            '0','1','2','3','4','5','6','7','8','9'
        };

        std::uniform_int_distribution<std::uint32_t> letter_dist(
            static_cast<std::uint32_t>(0),
            static_cast<std::uint32_t>(letters.size() - static_cast<std::size_t>(1))
        );
        std::uniform_int_distribution<std::uint32_t> digit_dist(
            static_cast<std::uint32_t>(0),
            static_cast<std::uint32_t>(digits.size() - static_cast<std::size_t>(1))
        );

        std::string result{};
        result.reserve(static_cast<std::string::size_type>(5));

        const std::uint32_t li1 = letter_dist(engine);
        const std::uint32_t li2 = letter_dist(engine);
        result.push_back(letters[static_cast<std::size_t>(li1)]);
        result.push_back(letters[static_cast<std::size_t>(li2)]);

        const std::uint32_t di1 = digit_dist(engine);
        const std::uint32_t di2 = digit_dist(engine);
        const std::uint32_t di3 = digit_dist(engine);
        result.push_back(digits[static_cast<std::size_t>(di1)]);
        result.push_back(digits[static_cast<std::size_t>(di2)]);
        result.push_back(digits[static_cast<std::size_t>(di3)]);

        return result;
    }
}  // anonymous namespace

robot::robot() : name_()
{
}

std::string robot::name() const
{
    std::lock_guard<std::mutex> lock(name_mutex_);
    if (name_.empty())
    {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock_name(name_mutex_);
    if (!name_.empty())
    {
        std::lock_guard<std::mutex> lock_set(g_mutex);
        (void)g_used_names.erase(name_);
        name_.clear();
    }
}

std::string robot::generate_unique_name()
{
    for (;;)
    {
        std::string candidate = generate_name_impl(prng());
        std::lock_guard<std::mutex> lock(g_mutex);
        const auto insert_result = g_used_names.insert(candidate);
        if (insert_result.second)
        {
            return candidate;
        }
    }
}

}  // namespace robot_name
