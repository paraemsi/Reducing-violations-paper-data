#include "robot_name.h"

#include <array>
#include <cstdint>
#include <random>

namespace robot_name {

using std::string;

std::unordered_set<string> robot::s_used_names{};
std::mutex                  robot::s_mutex{};

robot::robot() : m_name(generate_unique_name())
{
}

const string& robot::name() const
{
    return m_name;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if(!m_name.empty())
    {
        /* erase returns number erased; explicit discard to satisfy MISRA */
        (void)s_used_names.erase(m_name);
    }
    m_name = generate_unique_name();
}

string robot::generate_unique_name()
{
    static std::random_device rd{};
    static std::mt19937       engine{ rd() };

    static constexpr std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static constexpr std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::uint16_t> letter_dist(
        static_cast<std::uint16_t>(0U),
        static_cast<std::uint16_t>(letters.size() - 1U));
    std::uniform_int_distribution<std::uint16_t> digit_dist(
        static_cast<std::uint16_t>(0U),
        static_cast<std::uint16_t>(digits.size() - 1U));

    string candidate(5U, '\0');

    do
    {
        candidate[0U] = letters[static_cast<std::size_t>(letter_dist(engine))];
        candidate[1U] = letters[static_cast<std::size_t>(letter_dist(engine))];
        candidate[2U] = digits[static_cast<std::size_t>(digit_dist(engine))];
        candidate[3U] = digits[static_cast<std::size_t>(digit_dist(engine))];
        candidate[4U] = digits[static_cast<std::size_t>(digit_dist(engine))];
    } while(!is_name_unique(candidate));

    register_name(candidate);
    return candidate;
}

bool robot::is_name_unique(const string& candidate)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    return (s_used_names.find(candidate) == s_used_names.end());
}

void robot::register_name(const string& name)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    (void)s_used_names.insert(name);
}

}  // namespace robot_name
