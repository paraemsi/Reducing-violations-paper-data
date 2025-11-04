#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <mutex>
#include <cstdint>

namespace robot_name {

namespace
{
    // Protects access to used_names
    std::mutex& get_mutex()
    {
        static std::mutex mtx;
        return mtx;
    }

    // Set of all assigned robot names
    std::set<std::string>& used_names()
    {
        static std::set<std::string> names;
        return names;
    }

    // Random engine for name generation
    std::mt19937& rng()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}

bool Robot::is_name_used(const std::string& name)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    return (used_names().find(name) != used_names().end());
}

void Robot::register_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    (void)used_names().insert(name);
}

void Robot::unregister_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    (void)used_names().erase(name);
}

Robot::Robot()
    : m_name("")
{
    // Name is assigned on first use
}

std::string Robot::name() const
{
    if (m_name.empty())
    {
        // const_cast is safe here because we only mutate m_name
        const_cast<Robot*>(this)->assign_name();
    }
    return m_name;
}

void Robot::reset()
{
    if (!m_name.empty())
    {
        unregister_name(m_name);
        m_name.clear();
    }
}

void Robot::assign_name()
{
    static constexpr std::uint32_t max_attempts = 10000U;
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    for (std::uint32_t attempt = 0U; attempt < max_attempts; ++attempt)
    {
        std::string candidate;
        candidate += static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(rng())));
        candidate += static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(rng())));
        candidate += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(rng())));
        candidate += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(rng())));
        candidate += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(rng())));

        if (!is_name_used(candidate))
        {
            m_name = candidate;
            register_name(m_name);
            return;
        }
    }
    // If we get here, all attempts failed
    throw std::runtime_error("Unable to generate unique robot name");
}

}  // namespace robot_name
