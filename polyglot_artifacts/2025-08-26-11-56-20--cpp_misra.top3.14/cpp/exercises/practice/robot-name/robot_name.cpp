#include "robot_name.h"
#include <random>
#include <mutex>
#include <array>
#include <algorithm>

namespace robot_name {

namespace {
    // Use a mutex to protect the static set of used names
    std::mutex& get_mutex() {
        static std::mutex mtx;
        return mtx;
    }
}

::std::unordered_set<::std::string> robot::s_used_names;

robot::robot()
    : m_name("")
{
}

robot::~robot()
{
    // Remove the name from the set of used names if it exists
    if (!m_name.empty()) {
        ::std::lock_guard<::std::mutex> lock(get_mutex());
        (void)s_used_names.erase(m_name);
    }
}

::std::string robot::name(void)
{
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset(void)
{
    if (!m_name.empty()) {
        ::std::lock_guard<::std::mutex> lock(get_mutex());
        (void)s_used_names.erase(m_name);
        m_name.clear();
    }
}

::std::string robot::generate_unique_name(void)
{
    ::std::string new_name;
    ::std::lock_guard<::std::mutex> lock(get_mutex());
    do {
        new_name = generate_name();
    } while (s_used_names.find(new_name) != s_used_names.end());
    (void)s_used_names.insert(new_name);
    return new_name;
}

::std::string robot::generate_name(void)
{
    // Use fixed-width types for all numeric variables
    using letter_index_t = ::std::uint8_t;
    using digit_index_t = ::std::uint16_t;

    static ::std::random_device rd;
    static ::std::mt19937 gen(rd());
    static ::std::uniform_int_distribution<letter_index_t> letter_dist(0U, 25U);
    static ::std::uniform_int_distribution<digit_index_t> digit_dist(0U, 9U);

    ::std::array<char, 5U> name_arr{};

    // Generate two uppercase letters
    name_arr[0U] = static_cast<char>('A' + static_cast<letter_index_t>(letter_dist(gen)));
    name_arr[1U] = static_cast<char>('A' + static_cast<letter_index_t>(letter_dist(gen)));

    // Generate three digits
    name_arr[2U] = static_cast<char>('0' + static_cast<digit_index_t>(digit_dist(gen)));
    name_arr[3U] = static_cast<char>('0' + static_cast<digit_index_t>(digit_dist(gen)));
    name_arr[4U] = static_cast<char>('0' + static_cast<digit_index_t>(digit_dist(gen)));

    return ::std::string(name_arr.data(), name_arr.size());
}

}  // namespace robot_name
