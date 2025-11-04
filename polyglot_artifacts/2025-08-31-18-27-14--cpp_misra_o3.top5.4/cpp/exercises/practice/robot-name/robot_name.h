#ifndef ROBOT_NAME_H
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>
#include <array>
#include <cstdint>
#include <mutex>

namespace robot_name {

class Robot
{
public:
    Robot();

    const std::string& name() const noexcept;

    void reset();

private:
    static std::string generate_unique_name();

    static std::mt19937& rng();

    static std::unordered_set<std::string> s_used_names;

    std::string m_name;
};

/* Provide the lowercase alias expected by the tests */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
