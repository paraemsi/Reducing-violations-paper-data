#include "robot_name.h"
#include <random>
#include <set>
#include <mutex>
#include <utility>

namespace robot_name {

namespace
{
    // Use a mutex to protect the set of used names for thread safety
    std::set<std::string> used_names;
    std::mutex used_names_mutex;
    using name_set_t = std::set<std::string>;
}

robot_name::robot::robot()
    : m_name()
{
    // Robot starts with no name
}

std::string robot_name::robot::name() const
{
    if (m_name.empty())
    {
        // Remove constness to allow lazy initialization
        robot* mutable_this = const_cast<robot*>(this);
        mutable_this->m_name = generate_unique_name();
        register_name(mutable_this->m_name);
    }
    return m_name;
}

void robot_name::robot::reset()
{
    if (!m_name.empty())
    {
        unregister_name(m_name);
        m_name.clear();
    }
}

bool robot_name::robot::is_name_used(const std::string& candidate)
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    return (used_names.find(candidate) != used_names.end());
}

void robot_name::robot::register_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    (void)used_names.insert(name);
}

void robot_name::robot::unregister_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    (void)used_names.erase(name);
}

std::string robot_name::robot::generate_unique_name()
{
    // Use fixed-width types for MISRA compliance
    using letter_index_t = std::uint8_t;
    using digit_index_t = std::uint16_t;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<letter_index_t> letter_dist(0U, 25U);
    static std::uniform_int_distribution<digit_index_t> digit_dist(0U, 9U);

    std::string candidate;
    do
    {
        candidate.clear();
        candidate += static_cast<char>('A' + static_cast<letter_index_t>(letter_dist(gen)));
        candidate += static_cast<char>('A' + static_cast<letter_index_t>(letter_dist(gen)));
        candidate += static_cast<char>('0' + static_cast<digit_index_t>(digit_dist(gen)));
        candidate += static_cast<char>('0' + static_cast<digit_index_t>(digit_dist(gen)));
        candidate += static_cast<char>('0' + static_cast<digit_index_t>(digit_dist(gen)));
    }
    while (is_name_used(candidate));
    return candidate;
}

}  // namespace robot_name
