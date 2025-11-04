#include "robot_name.h"
#include <random>
#include <mutex>
#include <array>

namespace robot_name {

namespace {
    // Thread-safe random engine and mutex for name generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::mutex name_mutex;
    std::uniform_int_distribution<std::uint16_t> letter_dist(0, 25);
    std::uniform_int_distribution<std::uint16_t> digit_dist(0, 9);
}

std::unordered_set<std::string> robot::s_used_names;

robot::robot()
    : m_name("")
{
}

robot::~robot()
{
    // Remove name from used set on destruction
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(name_mutex);
        (void)s_used_names.erase(m_name);
    }
}

std::string robot::name(void)
{
    if (m_name.empty()) {
        generate_name();
    }
    return m_name;
}

void robot::reset(void)
{
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(name_mutex);
        (void)s_used_names.erase(m_name);
        m_name.clear();
    }
}

void robot::generate_name(void)
{
    std::string new_name;
    bool unique = false;

    while (!unique) {
        std::array<char, 5> arr;
        {
            std::lock_guard<std::mutex> lock(name_mutex);
            arr[0] = static_cast<char>('A' + letter_dist(gen));
            arr[1] = static_cast<char>('A' + letter_dist(gen));
            arr[2] = static_cast<char>('0' + digit_dist(gen));
            arr[3] = static_cast<char>('0' + digit_dist(gen));
            arr[4] = static_cast<char>('0' + digit_dist(gen));
            new_name = std::string(arr.data(), arr.size());

            if (s_used_names.find(new_name) == s_used_names.end()) {
                (void)s_used_names.insert(new_name);
                unique = true;
            }
        }
    }
    m_name = new_name;
}

}  // namespace robot_name
