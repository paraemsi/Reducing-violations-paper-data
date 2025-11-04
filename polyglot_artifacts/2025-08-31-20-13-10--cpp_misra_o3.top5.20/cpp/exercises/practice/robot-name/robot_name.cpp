#include "robot_name.h"

#include <random>
#include <unordered_set>
#include <mutex>
#include <string>

namespace
{
    using generator_type = std::mt19937;

    generator_type& rng()
    {
        static std::random_device rd;
        static generator_type gen(rd());
        return gen;
    }

    static std::unordered_set<std::string> used_names;
    static std::mutex used_names_mutex;
}   // unnamed namespace

namespace robot_name {

robot::robot() : m_name(generate_unique_name())
{
}

const std::string& robot::name() const noexcept
{
    return m_name;
}

void robot::reset()
{
    /* Keep every previously assigned name in the global
       set so that no robot can ever be issued the same
       identifier again, even after reset. */
    m_name = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits  = "0123456789";

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string new_name;
    bool unique_found = false;

    while(!unique_found)
    {
        new_name.clear();
        new_name += letters[static_cast<std::size_t>(letter_dist(rng()))];
        new_name += letters[static_cast<std::size_t>(letter_dist(rng()))];
        new_name += digits[static_cast<std::size_t>(digit_dist(rng()))];
        new_name += digits[static_cast<std::size_t>(digit_dist(rng()))];
        new_name += digits[static_cast<std::size_t>(digit_dist(rng()))];

        std::lock_guard<std::mutex> lock(used_names_mutex);
        if(used_names.find(new_name) == used_names.end())
        {
            used_names.insert(new_name);
            unique_found = true;
        }
    }

    return new_name;
}

}   // namespace robot_name
