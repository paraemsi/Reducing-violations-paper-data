#include "robot_name.h"

#include <unordered_set>
#include <random>
#include <array>
#include <mutex>

namespace robot_name {

namespace
{
    /*  Storage for already-allocated names and mutex for thread-safe access  */
    std::unordered_set<std::string> used_names {};
    std::mutex                       used_names_mutex {};
}  // unnamed namespace

robot::robot() : m_name(generate_unique_name())
{
}




const std::string& robot::name() const noexcept
{
    return m_name;
}

void robot::reset()
{
    m_name = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    static std::random_device                     rd {};
    static thread_local std::mt19937              generator(rd());
    static const std::array<char, 26U>            letters {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static const std::array<char, 10U>            digits {
        '0','1','2','3','4','5','6','7','8','9'
    };
    std::uniform_int_distribution<std::uint32_t>  letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t>  digit_dist(0U, 9U);

    std::string candidate {};
    candidate.reserve(5U);

    for (;;)
    {
        candidate.clear();

        candidate.push_back(
            letters[static_cast<std::size_t>(letter_dist(generator))]);
        candidate.push_back(
            letters[static_cast<std::size_t>(letter_dist(generator))]);
        candidate.push_back(
            digits[static_cast<std::size_t>(digit_dist(generator))]);
        candidate.push_back(
            digits[static_cast<std::size_t>(digit_dist(generator))]);
        candidate.push_back(
            digits[static_cast<std::size_t>(digit_dist(generator))]);

        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (used_names.insert(candidate).second)
        {
            break;
        }
    }

    return candidate;
}

}  // namespace robot_name
