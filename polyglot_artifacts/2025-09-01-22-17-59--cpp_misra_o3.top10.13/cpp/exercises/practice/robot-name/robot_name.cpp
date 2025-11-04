#include "robot_name.h"

#include <array>
#include <unordered_set>
#include <random>
#include <mutex>

namespace robot_name {

namespace
{
    /* store names that are already in use */
    std::unordered_set<std::string> used_names{};
    std::mutex used_names_mutex{};

    /* generate a random candidate name (may collide) */
    std::string generate_random_name(std::mt19937& engine)
    {
        static constexpr std::array<char, 26U> letters{
            'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

        static constexpr std::array<char, 10U> digits{
            '0','1','2','3','4','5','6','7','8','9'};

        std::uniform_int_distribution<std::uint16_t> letter_dist{0U, 25U};
        std::uniform_int_distribution<std::uint16_t> digit_dist{0U, 9U};

        std::string name{};
        name.reserve(5U);

        name.push_back(letters[static_cast<std::size_t>(letter_dist(engine))]);
        name.push_back(letters[static_cast<std::size_t>(letter_dist(engine))]);

        for(std::uint8_t i{0U}; i < static_cast<std::uint8_t>(3); ++i)
        {
            name.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);
        }

        return name;
    }
} // anonymous namespace

std::string Robot::generate_unique_name()
{
    static std::random_device rd{};
    static std::mt19937 engine{rd()};

    for(;;)
    {
        std::string candidate{generate_random_name(engine)};

        std::lock_guard<std::mutex> lock(used_names_mutex);

        auto const insert_result = used_names.insert(candidate);
        if(insert_result.second)
        {
            return candidate;
        }
    }
}

Robot::Robot() : m_name{generate_unique_name()}
{
}

Robot::~Robot()
{
    if(!m_name.empty())
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        (void)used_names.erase(m_name);
    }
}

const std::string& Robot::name() const
{
    return m_name;
}

void Robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        (void)used_names.erase(m_name);
    }

    m_name = generate_unique_name();
}

}  // namespace robot_name
