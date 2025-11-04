#include "robot_name.h"
#include <cstdint>
#include <string>
#include <unordered_set>
#include <random>
#include <array>
#include <mutex>

namespace robot_name {

namespace
{
    using generator_type = std::mt19937;

    // Mutex protecting shared resources
    std::mutex& name_mutex()
    {
        static std::mutex m;
        return m;
    }

    // Random engine seeded with random_device
    generator_type& random_engine()
    {
        static generator_type engine{ std::random_device{}() };
        return engine;
    }

    // Produce a random candidate name (may collide)
    std::string generate_random_name()
    {
        static const std::array<char, 26U> letters = {
            'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
        };
        static const std::array<char, 10U> digits = {
            '0','1','2','3','4','5','6','7','8','9'
        };

        std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
        std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

        std::string candidate;
        candidate.reserve(5U);

        for (std::uint32_t i = 0U; i < 2U; ++i)
        {
            candidate.push_back(letters[letter_dist(random_engine())]);
        }

        for (std::uint32_t i = 0U; i < 3U; ++i)
        {
            candidate.push_back(digits[digit_dist(random_engine())]);
        }

        return candidate;
    }

    // Set storing used names to guarantee uniqueness
    std::unordered_set<std::string>& used_names()
    {
        static std::unordered_set<std::string> set;
        return set;
    }

} // unnamed namespace

robot::robot() : m_name()
{
    /* Name is generated lazily */
}

robot::~robot()
{
    std::lock_guard<std::mutex> lock(name_mutex());
    if (!m_name.empty())
    {
        (void)used_names().erase(m_name);
    }
}

const std::string& robot::name() const
{
    if (m_name.empty())
    {
        std::lock_guard<std::mutex> lock(name_mutex());
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock(name_mutex());
    if (!m_name.empty())
    {
        (void)used_names().erase(m_name);
        m_name.clear();
    }
}

std::string robot::generate_unique_name()
{
    std::string candidate;

    do
    {
        candidate = generate_random_name();
    } while (used_names().find(candidate) != used_names().end());

    (void)used_names().insert(candidate);

    return candidate;
}

}  // namespace robot_name
