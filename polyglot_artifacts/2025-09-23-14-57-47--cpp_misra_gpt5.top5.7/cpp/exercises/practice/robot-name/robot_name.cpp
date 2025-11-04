#include "robot_name.h"

#include <array>
#include <cstddef>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    // Character tables (no arithmetic on character codes)
    constexpr std::array<char, 26U> LETTERS{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    constexpr std::array<char, 10U> DIGITS{
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::unordered_set<std::string> g_assigned{};
    std::mutex g_mutex{};

    std::string generate_name()
    {
        static std::random_device rd{};
        std::size_t const last_letter_index = (LETTERS.size() - static_cast<std::size_t>(1U));
        std::size_t const last_digit_index = (DIGITS.size() - static_cast<std::size_t>(1U));
        std::uniform_int_distribution<std::size_t> letter_idx(static_cast<std::size_t>(0U), last_letter_index);
        std::uniform_int_distribution<std::size_t> digit_idx(static_cast<std::size_t>(0U), last_digit_index);

        std::string n;
        n.reserve(5U);
        n.push_back(LETTERS.at(letter_idx(rd)));
        n.push_back(LETTERS.at(letter_idx(rd)));
        n.push_back(DIGITS.at(digit_idx(rd)));
        n.push_back(DIGITS.at(digit_idx(rd)));
        n.push_back(DIGITS.at(digit_idx(rd)));
        return n;
    }

    std::string generate_unique_name()
    {
        for (;;)
        {
            std::string n = generate_name();
            std::lock_guard<std::mutex> lock(g_mutex);
            bool const inserted = g_assigned.insert(n).second;
            if (inserted)
            {
                return n;
            }
        }
    }
}  // namespace

robot::robot() noexcept
    : m_name()
{
}

robot::~robot() noexcept
{
    if (!m_name.empty())
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        (void)g_assigned.erase(m_name);
    }
}

const std::string& robot::name() const
{
    if (m_name.empty())
    {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset()
{
    if (!m_name.empty())
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        (void)g_assigned.erase(m_name);
        m_name.clear();
    }
}

}  // namespace robot_name
