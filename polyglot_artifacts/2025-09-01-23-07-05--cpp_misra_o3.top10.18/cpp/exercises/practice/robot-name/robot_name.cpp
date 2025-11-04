#include "robot_name.h"
#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace {

static std::unordered_set<std::string> s_used_names{};
static std::mutex s_mutex{};

static std::mt19937& rng_instance()
{
    static std::random_device rd{};
    static std::mt19937 rng{rd()};
    return rng;
}

static std::string generate_name_internal()
{
    static const std::array<char, 26U> letters{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    static const std::array<char, 10U> digits{
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    std::uniform_int_distribution<std::size_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::size_t> digit_dist(0U, 9U);

    std::string candidate{};
    candidate.reserve(5U);

    candidate.push_back(letters[letter_dist(rng_instance())]);
    candidate.push_back(letters[letter_dist(rng_instance())]);

    for (std::uint32_t i{0U}; (i < 3U); ++i)
    {
        candidate.push_back(digits[digit_dist(rng_instance())]);
    }

    return candidate;
}

}  // unnamed namespace

namespace robot_name {

std::string Robot::generate_unique_name()
{
    for (;;)
    {
        const std::string candidate = generate_name_internal();
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            const auto inserted = s_used_names.insert(candidate);
            if (inserted.second)
            {
                return candidate;
            }
        }
    }
}

Robot::Robot() : m_name(generate_unique_name())
{
}

const std::string& Robot::name() const
{
    return m_name;
}

void Robot::reset()
{
    m_name = generate_unique_name();
}

}  // namespace robot_name
