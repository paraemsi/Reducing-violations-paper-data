#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    std::mutex used_mutex;

    std::mt19937& rng()
    {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

    std::string random_name(std::mt19937& engine)
    {
        static std::uniform_int_distribution<int> letters(0, 25);
        static std::uniform_int_distribution<int> digits(0, 9);

        std::string n;
        n.reserve(5);
        n.push_back(static_cast<char>('A' + letters(engine)));
        n.push_back(static_cast<char>('A' + letters(engine)));
        n.push_back(static_cast<char>('0' + digits(engine)));
        n.push_back(static_cast<char>('0' + digits(engine)));
        n.push_back(static_cast<char>('0' + digits(engine)));
        return n;
    }

    std::string acquire_unique_name()
    {
        std::lock_guard<std::mutex> lock(used_mutex);
        auto& engine = rng();
        for (;;) {
            auto candidate = random_name(engine);
            if (used_names.insert(candidate).second) {
                return candidate;
            }
        }
    }

    void release_name(const std::string& n)
    {
        if (n.empty()) return;
        std::lock_guard<std::mutex> lock(used_mutex);
        used_names.erase(n);
    }
}  // namespace

robot::robot()
    : name_(acquire_unique_name())
{
}

robot::~robot()
{
    release_name(name_);
}

robot::robot(robot&& other) noexcept
    : name_(std::move(other.name_))
{
    other.name_.clear();
}

robot& robot::operator=(robot&& other) noexcept
{
    if (this != &other) {
        release_name(name_);
        name_ = std::move(other.name_);
        other.name_.clear();
    }
    return *this;
}

const std::string& robot::name() const
{
    return name_;
}

void robot::reset()
{
    auto new_name = acquire_unique_name();
    release_name(name_);
    name_ = std::move(new_name);
}

}  // namespace robot_name
