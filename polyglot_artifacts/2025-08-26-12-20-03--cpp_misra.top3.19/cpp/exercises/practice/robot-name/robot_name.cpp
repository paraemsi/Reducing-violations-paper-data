#include "robot_name.h"
#include <random>
#include <mutex>
#include <array>
#include <algorithm>

namespace robot_name {

::std::unordered_set<::std::string> robot::s_used_names;

namespace {
    // Use a function-local static to ensure thread-safe initialization
    std::mt19937& get_rng() {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        return rng;
    }
    std::mutex& get_mutex() {
        static std::mutex mtx;
        return mtx;
    }
} // anonymous namespace

robot::robot()
    : m_name("")
{
}

robot::~robot()
{
    // Remove name from used set if it exists
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
    ::std::string candidate;
    ::std::lock_guard<::std::mutex> lock(get_mutex());
    do {
        candidate = generate_name_candidate();
    } while (s_used_names.find(candidate) != s_used_names.end());
    (void)s_used_names.insert(candidate);
    return candidate;
}

::std::string robot::generate_name_candidate(void)
{
    // Use fixed-width types for indices
    using letter_index_t = ::std::uint8_t;
    using digit_index_t = ::std::uint8_t;

    static const ::std::array<char, 26> letters = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static const ::std::array<char, 10> digits = {
        '0','1','2','3','4','5','6','7','8','9'
    };

    ::std::mt19937& rng = get_rng();
    ::std::uniform_int_distribution<letter_index_t> letter_dist(0U, 25U);
    ::std::uniform_int_distribution<digit_index_t> digit_dist(0U, 9U);

    ::std::string result;
    result += letters[letter_dist(rng)];
    result += letters[letter_dist(rng)];
    result += digits[digit_dist(rng)];
    result += digits[digit_dist(rng)];
    result += digits[digit_dist(rng)];
    return result;
}

}  // namespace robot_name
