#include "robot_name.h"

#include <array>
#include <random>
#include <mutex>

namespace robot_name {

std::unordered_set<std::string> robot::s_used_names{};
std::mutex robot::s_mutex{};

robot::robot() : m_name{ generate_unique_name() }
{
}

const std::string& robot::name() const
{
    return m_name;
}

void robot::reset()
{
    /* Preserve all previously-used names to guarantee uniqueness for the
     * lifetime of the program (tests expect no reuse after resets). */
    m_name = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    std::lock_guard<std::mutex> guard(s_mutex);

    static constexpr std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    static constexpr std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'
    };

    static std::mt19937 rng{ std::random_device{}() };
    static std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    static std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    for (;;) { /* generate until unique */
        std::string candidate{};
        candidate.reserve(5U);
        candidate.push_back(letters[letter_dist(rng)]);
        candidate.push_back(letters[letter_dist(rng)]);

        for (std::uint32_t i{ 0U }; i < 3U; ++i) {
            candidate.push_back(digits[digit_dist(rng)]);
        }

        const auto inserted = s_used_names.insert(candidate);
        if (inserted.second) {
            return candidate;
        }
    }
}

}  // namespace robot_name
