#include "robot_name.h"

#include <unordered_set>
#include <mutex>
#include <random>
#include <string>
#include <cstdint>

namespace
{
    constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr char digits[] = "0123456789";

    std::unordered_set<std::string> g_assigned_names{};
    std::mutex g_mutex{};

    // Obtain a reference to a thread-local random engine to avoid data races
    std::mt19937& rng()
    {
        static thread_local std::mt19937 engine{std::random_device{}()};
        return engine;
    }

    // Uniform distributions for letters and digits
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string generate_unique_name_internal()
    {
        std::string candidate;

        for (;;)
        {
            char name_chars[5];
            name_chars[0] = letters[static_cast<std::size_t>(letter_dist(rng()))];
            name_chars[1] = letters[static_cast<std::size_t>(letter_dist(rng()))];
            name_chars[2] = digits[static_cast<std::size_t>(digit_dist(rng()))];
            name_chars[3] = digits[static_cast<std::size_t>(digit_dist(rng()))];
            name_chars[4] = digits[static_cast<std::size_t>(digit_dist(rng()))];

            candidate.assign(name_chars, 5U);

            {
                std::lock_guard<std::mutex> lock(g_mutex);
                if (g_assigned_names.insert(candidate).second)
                {
                    break;
                }
            }
        }

        return candidate;
    }
} // anonymous namespace

namespace robot_name
{

Robot::Robot() : m_name(generate_unique_name())
{
}

Robot::~Robot()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    (void)g_assigned_names.erase(m_name);
}

const std::string& Robot::name() const
{
    return m_name;
}

void Robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        (void)g_assigned_names.erase(m_name);
    }
    m_name = generate_unique_name();
}

std::string Robot::generate_unique_name()
{
    return generate_unique_name_internal();
}

}  // namespace robot_name
