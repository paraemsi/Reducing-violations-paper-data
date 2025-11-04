#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

namespace
{
    // Use a function-local static to ensure thread-safe initialization
    std::mutex& name_mutex()
    {
        static std::mutex mtx;
        return mtx;
    }

    // Random engine for name generation
    std::mt19937& rng()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}

std::unordered_set<std::string>& robot::assigned_names(void)
{
    static std::unordered_set<std::string> names;
    return names;
}

robot::robot()
    : m_name()
{
    // Name is generated lazily on first call to name()
}

robot::~robot()
{
    if (!m_name.empty())
    {
        std::lock_guard<std::mutex> lock(name_mutex());
        (void)assigned_names().erase(m_name);
    }
}

std::string robot::name(void)
{
    if (m_name.empty())
    {
        generate_name();
    }
    return m_name;
}

void robot::reset()
{
    if (!m_name.empty())
    {
        std::lock_guard<std::mutex> lock(name_mutex());
        (void)assigned_names().erase(m_name);
        m_name.clear();
    }
}

void robot::generate_name(void)
{
    static constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr std::size_t num_letters = 26U;
    static constexpr std::uint32_t max_tries = 10000U;

    std::lock_guard<std::mutex> lock(name_mutex());

    for (std::uint32_t attempt = 0U; attempt < max_tries; ++attempt)
    {
        std::string new_name;
        // Two uppercase letters
        for (std::uint32_t i = 0U; i < 2U; ++i)
        {
            std::uniform_int_distribution<std::uint32_t> dist(0U, num_letters - 1U);
            new_name += letters[static_cast<std::size_t>(dist(rng()))];
        }
        // Three digits
        for (std::uint32_t i = 0U; i < 3U; ++i)
        {
            std::uniform_int_distribution<std::uint32_t> dist(0U, 9U);
            new_name += static_cast<char>('0' + static_cast<std::int32_t>(dist(rng())));
        }

        if (assigned_names().find(new_name) == assigned_names().end())
        {
            assigned_names().insert(new_name);
            m_name = new_name;
            return;
        }
    }
    // If we get here, we failed to generate a unique name
    throw std::runtime_error("Unable to generate unique robot name");
}

}  // namespace robot_name
