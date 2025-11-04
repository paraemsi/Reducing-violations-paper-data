#include "robot_name.h"

namespace robot_name {

std::unordered_set<std::string> Robot::s_used_names{};
std::mutex Robot::s_mutex{};

Robot::Robot() : m_name{}
{
}

const std::string& Robot::name() const
{
    if (m_name.empty())
    {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!m_name.empty())
    {
        (void)s_used_names.erase(m_name);
    }
    m_name.clear();
}

std::mt19937& Robot::get_rng()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    return rng;
}

std::string Robot::generate_unique_name()
{
    static const std::array<char, 26U> letters{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    static const std::array<char, 10U> digits{
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    auto& rng = get_rng();
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string name_local;
    while (true)
    {
        name_local.clear();
        name_local.push_back(letters[static_cast<std::size_t>(letter_dist(rng))]);
        name_local.push_back(letters[static_cast<std::size_t>(letter_dist(rng))]);

        for (std::uint32_t i = 0U; i < static_cast<std::uint32_t>(3); ++i)
        {
            name_local.push_back(digits[static_cast<std::size_t>(digit_dist(rng))]);
        }

        std::lock_guard<std::mutex> lock(s_mutex);
        if (s_used_names.insert(name_local).second)
        {
            break;
        }
    }

    return name_local;
}

}  // namespace robot_name
