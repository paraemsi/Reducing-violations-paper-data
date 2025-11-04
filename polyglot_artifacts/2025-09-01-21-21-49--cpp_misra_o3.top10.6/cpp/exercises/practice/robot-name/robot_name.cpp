#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>
#include <cstdint>
#include <array>

namespace robot_name {

namespace {

/*  Global set of already assigned names to guarantee uniqueness.
 *  Guarded by a mutex to ensure thread-safety.
 */
static std::unordered_set<std::string> g_used_names {};
static std::mutex                      g_names_mutex {};

std::string make_random_name(std::mt19937& engine)
{
    static const std::array<char, 26U> alphabet {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static const std::array<char, 10U> digits {
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string result {};
    result.reserve(5U);

    result.push_back(alphabet[static_cast<std::size_t>(letter_dist(engine))]);
    result.push_back(alphabet[static_cast<std::size_t>(letter_dist(engine))]);
    result.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);
    result.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);
    result.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);

    return result;
}

} // unnamed namespace

Robot::Robot() : m_name()
{
    /* ctor leaves the name empty until first call to name() */
}

const std::string& Robot::name()
{
    if(m_name.empty())
    {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset()
{
    if(!m_name.empty())
    {
        std::lock_guard<std::mutex> guard(g_names_mutex);
        (void)g_used_names.erase(m_name); /* MISRA-compliant explicit discard */
        m_name.clear();
    }
}

std::string Robot::generate_unique_name()
{
    static std::random_device rd {};
    static std::mt19937       engine(rd());

    for(;;)
    {
        const std::string candidate { make_random_name(engine) };

        std::lock_guard<std::mutex> guard(g_names_mutex);
        const auto inserted = g_used_names.insert(candidate);
        if(inserted.second)
        {
            return candidate;
        }
    }
}

}  // namespace robot_name
