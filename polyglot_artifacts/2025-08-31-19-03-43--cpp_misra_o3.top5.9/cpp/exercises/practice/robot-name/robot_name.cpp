#include "robot_name.h"

#include <array>
#include <random>

namespace robot_name {

std::unordered_set<std::string> Robot::s_used_names {};
std::mutex Robot::s_mutex {};

Robot::Robot()
    : m_name(generate_unique_name())
{
}

const std::string& Robot::name() const noexcept
{
    return m_name;
}

void Robot::reset()
{
    const std::string old_name { m_name };

    {
        std::lock_guard<std::mutex> lock(s_mutex);
        (void)s_used_names.erase(old_name);
    }

    for (;;)
    {
        const std::string new_name { generate_unique_name() };

        if (new_name != old_name)
        {
            m_name = new_name;
            break;
        }
    }
}

std::string Robot::generate_unique_name()
{
    for (;;)
    {
        const std::string candidate = generate_random_name();
        std::lock_guard<std::mutex> lock(s_mutex);

        if (s_used_names.insert(candidate).second)
        {
            return candidate;
        }
    }
}

std::string Robot::generate_random_name()
{
    static std::random_device rd {};
    static std::mt19937 engine { rd() };
    static std::uniform_int_distribution<std::uint32_t> letter_dist { 0U, 25U };
    static std::uniform_int_distribution<std::uint32_t> digit_dist { 0U, 9U };

    static constexpr std::array<char, 26U> letters
    {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    static constexpr std::array<char, 10U> digits
    {
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::string result {};
    result.reserve(5U);

    result.push_back(letters[letter_dist(engine)]);
    result.push_back(letters[letter_dist(engine)]);
    result.push_back(digits[digit_dist(engine)]);
    result.push_back(digits[digit_dist(engine)]);
    result.push_back(digits[digit_dist(engine)]);

    return result;
}

bool Robot::is_name_unique(const std::string& candidate)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    return (s_used_names.find(candidate) == s_used_names.end());
}

void Robot::register_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    (void)s_used_names.insert(name);
}

}  // namespace robot_name
