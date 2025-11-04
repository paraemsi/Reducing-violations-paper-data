#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

std::unordered_set<name_string> robot::s_used_names;

namespace {
    std::mutex& get_mutex() {
        static std::mutex mtx;
        return mtx;
    }
}

robot::robot()
    : m_name("")
{
    // Robot starts unnamed
}

robot::~robot()
{
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(get_mutex());
        release_name(m_name);
    }
}

name_string robot::name()
{
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock(get_mutex());
    if (!m_name.empty()) {
        release_name(m_name);
        m_name.clear();
    }
}

name_string robot::generate_unique_name()
{
    std::lock_guard<std::mutex> lock(get_mutex());
    name_string new_name;
    do {
        new_name = generate_random_name();
    } while (s_used_names.find(new_name) != s_used_names.end());
    s_used_names.insert(new_name);
    return new_name;
}

name_string robot::generate_random_name()
{
    // Use random_device and mt19937 for randomness
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    static thread_local std::uniform_int_distribution<std::uint16_t> letter_dist(0, 25);
    static thread_local std::uniform_int_distribution<std::uint16_t> digit_dist(0, 9);

    name_string result;
    result += static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(gen)));
    result += static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(gen)));
    result += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(gen)));
    result += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(gen)));
    result += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(gen)));
    return result;
}

void robot::release_name(const name_string& name)
{
    s_used_names.erase(name);
}

}  // namespace robot_name
