#include "robot_name.h"

#include <unordered_set>
#include <random>
#include <mutex>
#include <cstddef>

namespace robot_name {

namespace
{
/* Anonymous-namespace helpers & state
 * -----------------------------------
 * A global name registry guarantees uniqueness across every
 * robot instance created within the current process.
 */
std::unordered_set<std::string>            used_names_ {};
std::mt19937                               rng_ { std::random_device {}() };
std::mutex                                 mtx_    {};

/* Character pools */
const std::string kLetters { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::string kDigits  { "0123456789" };

/* Random selection helpers */
std::string random_letters(std::size_t count)
{
    std::string result {};
    result.reserve(count);

    std::uniform_int_distribution<std::size_t> dist { static_cast<std::size_t>(0U),
                                                      (kLetters.size() - static_cast<std::size_t>(1U)) };

    for (std::size_t i { 0U }; (i < count); ++i)
    {
        result.push_back(kLetters[dist(rng_)]);
    }

    return result;
}

std::string random_digits(std::size_t count)
{
    std::string result {};
    result.reserve(count);

    std::uniform_int_distribution<std::size_t> dist { static_cast<std::size_t>(0U),
                                                      (kDigits.size() - static_cast<std::size_t>(1U)) };

    for (std::size_t i { 0U }; (i < count); ++i)
    {
        result.push_back(kDigits[dist(rng_)]);
    }

    return result;
}
}  // unnamed namespace

/* robot implementation
 * -------------------- */
robot::robot() : current_name_ {}
{
    /* Defer actual name creation until first call to name() */
}

const std::string& robot::name() const
{
    if (current_name_.empty())
    {
        generate_name();
    }

    return current_name_;
}

void robot::reset() const
{
    std::lock_guard<std::mutex> lock { mtx_ };

    if (!current_name_.empty())
    {
        (void)used_names_.erase(current_name_);
        current_name_.clear();
    }
}

void robot::generate_name() const
{
    std::string candidate {};

    for (;;)
    {
        candidate = random_letters(static_cast<std::size_t>(2U)) +
                    random_digits(static_cast<std::size_t>(3U));

        /* Protect shared registry */
        std::lock_guard<std::mutex> lock { mtx_ };

        if (used_names_.find(candidate) == used_names_.end())
        {
            /* Unique – reserve and exit loop */
            (void)used_names_.insert(candidate);
            current_name_ = candidate;
            break;
        }
    }
}

}  // namespace robot_name
