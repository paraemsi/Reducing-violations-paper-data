#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

std::unordered_set<robot_name_string> Robot::s_used_names;

namespace {
    // Use a function-local static mutex to protect s_used_names
    std::mutex& get_mutex() {
        static std::mutex mtx;
        return mtx;
    }
}

Robot::Robot()
    : m_name("")
{
    // Robot starts with no name
}

Robot::~Robot() {
    std::lock_guard<std::mutex> lock(get_mutex());
    if (!m_name.empty()) {
        (void)s_used_names.erase(m_name);
    }
}

robot_name_string Robot::name() {
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset() {
    std::lock_guard<std::mutex> lock(get_mutex());
    if (!m_name.empty()) {
        (void)s_used_names.erase(m_name);
        m_name.clear();
    }
}

robot_name_string Robot::generate_unique_name() {
    std::lock_guard<std::mutex> lock(get_mutex());
    robot_name_string new_name;
    do {
        new_name = generate_random_name();
    } while (s_used_names.find(new_name) != s_used_names.end());
    s_used_names.insert(new_name);
    return new_name;
}

robot_name_string Robot::generate_random_name() {
    // Use random_device and mt19937 for randomness
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    static thread_local std::uniform_int_distribution<std::uint16_t> letter_dist(0, 25);
    static thread_local std::uniform_int_distribution<std::uint16_t> digit_dist(0, 9);

    char name[6] = {0};
    name[0] = static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(gen)));
    name[1] = static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(gen)));
    name[2] = static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(gen)));
    name[3] = static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(gen)));
    name[4] = static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(gen)));
    name[5] = '\0';
    return robot_name_string(name);
}

void Robot::release_name(const robot_name_string& name) {
    std::lock_guard<std::mutex> lock(get_mutex());
    (void)s_used_names.erase(name);
}

}  // namespace robot_name
