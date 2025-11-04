#include "robot_name.h"

#include <array>
#include <mutex>

namespace robot_name {

static const std::array<char, 26U> LETTERS = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                               'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                               'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                               'V', 'W', 'X', 'Y', 'Z' };

static const std::array<char, 10U> DIGITS = { '0', '1', '2', '3', '4',
                                             '5', '6', '7', '8', '9' };

std::unordered_set<std::string> Robot::s_used_names{};

/* Mutex protecting both the PRNG and the used-name set – kept at translation-unit scope */
static std::mutex s_mutex{};

Robot::Robot() : m_name(generate_unique_name())
{
}

const std::string& Robot::name() const noexcept
{
    return m_name;
}

void Robot::reset()
{
    m_name = generate_unique_name();
}

std::string Robot::generate_unique_name()
{
    /* Distributions for random selection of letters and digits */
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    for(;;)
    {
        std::string candidate{};
        candidate.reserve(5U);

        /* Protect both RNG state and the set of used names */
        std::lock_guard<std::mutex> lock(s_mutex);

        candidate.push_back(LETTERS[static_cast<std::size_t>(letter_dist(rng()))]);
        candidate.push_back(LETTERS[static_cast<std::size_t>(letter_dist(rng()))]);

        for(std::uint32_t i{0U}; i < static_cast<std::uint32_t>(3U); ++i)
        {
            candidate.push_back(DIGITS[static_cast<std::size_t>(digit_dist(rng()))]);
        }

        if(s_used_names.find(candidate) == s_used_names.end())
        {
            (void)s_used_names.insert(candidate);
            return candidate;     /* unique name created */
        }
        /* otherwise loop again and create a new candidate */
    }
}

std::mt19937& Robot::rng()
{
    static std::random_device rd{};
    static std::mt19937 engine{rd()};
    return engine;
}

}  // namespace robot_name
