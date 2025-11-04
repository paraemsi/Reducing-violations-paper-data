#include "robot_name.h"

#include <array>
#include <random>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {

/* Generate a random candidate name using the required pattern
 * – two uppercase letters followed by three decimal digits.
 * Does not check for uniqueness – caller must ensure that.
 */
std::string generate_name(std::mt19937& rng)
{
    static constexpr std::array<char, 26U> letters = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static constexpr std::array<char, 10U> digits = {
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string result;
    result.reserve(5U);

    for(std::uint32_t i = 0U; i < 2U; ++i)
    {
        const std::uint32_t idx = letter_dist(rng);
        result.push_back(letters[idx]);
    }

    for(std::uint32_t i = 0U; i < 3U; ++i)
    {
        const std::uint32_t idx = digit_dist(rng);
        result.push_back(digits[idx]);
    }

    return result;
}

/* Global bookkeeping of names currently in use.
 * Protected by a mutex because robots may be constructed / reset concurrently.
 */
std::unordered_set<std::string> used_names;
std::mutex used_names_mutex;

} // unnamed namespace


/* static */ std::string robot::generate_unique_name()
{
    static thread_local std::mt19937 rng{ std::random_device{}() };

    std::string candidate;

    do
    {
        candidate = generate_name(rng);

        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (used_names.find(candidate) == used_names.end())
        {
            used_names.insert(candidate);
            break;
        }
    } while (true);

    return candidate;
}

robot::robot() :
    m_name(generate_unique_name())
{
}

robot::~robot()
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    (void)used_names.erase(m_name);
}

const std::string& robot::name() const
{
    return m_name;
}

void robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        (void)used_names.erase(m_name);
    }

    m_name = generate_unique_name();
}

}  // namespace robot_name
