#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

std::unordered_set<robot_name_string>& robot::s_used_names()
{
    static std::unordered_set<robot_name_string> instance;
    return instance;
}

namespace {
    // Thread-safe random engine and mutex for name generation
    std::random_device rd;
    std::mt19937 engine(rd());
    std::mutex name_mutex;
}

robot::robot()
    : m_name("")
{
    // Robot starts unnamed
}

robot::~robot()
{
    std::lock_guard<std::mutex> lock(name_mutex);
    if (!m_name.empty()) {
        (void)s_used_names().erase(m_name);
    }
}

robot_name_string robot::name() const
{
    if (m_name.empty()) {
        // const_cast is safe here because we only want to lazily assign the name
        const_cast<robot*>(this)->m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock(name_mutex);
    if (!m_name.empty()) {
        (void)s_used_names().erase(m_name);
        m_name.clear();
    }
}

robot_name_string robot::generate_unique_name()
{
    std::lock_guard<std::mutex> lock(name_mutex);
    robot_name_string new_name;
    do {
        new_name = generate_random_name();
    } while (s_used_names().find(new_name) != s_used_names().end());
    (void)s_used_names().insert(new_name);
    return new_name;
}

robot_name_string robot::generate_random_name()
{
    // 2 uppercase letters + 3 digits
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::uint32_t num_letters = 26U;
    static const std::uint32_t num_digits = 10U;

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, num_letters - 1U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, num_digits - 1U);

    robot_name_string result;
    result += letters[static_cast<std::size_t>(letter_dist(engine))];
    result += letters[static_cast<std::size_t>(letter_dist(engine))];
    result += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(engine)));
    result += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(engine)));
    result += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(engine)));
    return result;
}


}  // namespace robot_name
