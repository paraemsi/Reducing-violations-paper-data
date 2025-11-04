#include "robot_name.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

/* Container holding all names currently in use */
std::unordered_set<std::string> used_names {};
/* Mutex to protect the shared container */
std::mutex used_names_mutex {};

/* Generate a random candidate name (may collide) */
std::string generate_name()
{
    static std::mt19937 rng { std::random_device {}() };

    static const std::array<char, 26U> letters {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static const std::array<char, 10U> digits {
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string candidate(5U, '\0');

    candidate[0U] = letters[static_cast<std::size_t>(letter_dist(rng))];
    candidate[1U] = letters[static_cast<std::size_t>(letter_dist(rng))];
    candidate[2U] = digits[static_cast<std::size_t>(digit_dist(rng))];
    candidate[3U] = digits[static_cast<std::size_t>(digit_dist(rng))];
    candidate[4U] = digits[static_cast<std::size_t>(digit_dist(rng))];

    return candidate;
}

}   // unnamed namespace

std::string robot::generate_unique_name()
{
    std::string candidate {};

    for (;;)
    {
        candidate = generate_name();

        {
            std::lock_guard<std::mutex> guard(used_names_mutex);
            if (used_names.find(candidate) == used_names.end())
            {
                (void)used_names.insert(candidate);
                break;
            }
        }
    }

    return candidate;
}

const std::string& robot::name() const
{
    if (name_.empty())
    {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset()
{
    if (!name_.empty())
    {
        std::lock_guard<std::mutex> guard(used_names_mutex);
        (void)used_names.erase(name_);
        name_.clear();
    }
}

robot::~robot()
{
    if (!name_.empty())
    {
        std::lock_guard<std::mutex> guard(used_names_mutex);
        (void)used_names.erase(name_);
    }
}

}   // namespace robot_name
