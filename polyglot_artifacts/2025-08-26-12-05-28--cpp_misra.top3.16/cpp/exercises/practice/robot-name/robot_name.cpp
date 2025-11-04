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
    using random_engine_t = std::mt19937;
    random_engine_t& get_rng()
    {
        // Thread-safe static initialization
        static thread_local random_engine_t rng{std::random_device{}()};
        return rng;
    }
}

bool robot::is_name_used(const std::string& candidate)
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    return (used_names.find(candidate) != used_names.end());
}

void robot::register_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    (void)used_names.insert(name);
}

void robot::unregister_name(const std::string& name)
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    (void)used_names.erase(name);
}

std::string robot::generate_unique_name()
{
    // Name format: two uppercase letters + three digits
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::uint32_t num_letters = 26U;
    static const std::uint32_t num_digits = 10U;

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, (num_letters - 1U));
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, (num_digits - 1U));

    std::string candidate;
    do
    {
        candidate.clear();
        candidate += letters[letter_dist(get_rng())];
        candidate += letters[letter_dist(get_rng())];
        candidate += static_cast<char>('0' + static_cast<char>(digit_dist(get_rng())));
        candidate += static_cast<char>('0' + static_cast<char>(digit_dist(get_rng())));
        candidate += static_cast<char>('0' + static_cast<char>(digit_dist(get_rng())));
    }
    while (is_name_used(candidate));

    register_name(candidate);
    return candidate;
}

robot::robot()
    : m_name()
{
    // Robot starts with no name
}

std::string robot::name()
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
        unregister_name(m_name);
        m_name.clear();
    }
}

}  // namespace robot_name
