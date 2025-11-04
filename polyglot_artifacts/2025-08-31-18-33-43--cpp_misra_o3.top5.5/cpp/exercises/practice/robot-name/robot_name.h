#pragma once

#include <string>
#include <unordered_set>
#include <cstdint>
#include <mutex>

namespace robot_name {

class robot
{
public:
    robot();

    const std::string& name() const;

    void reset();

private:
    std::string m_name;
    static std::unordered_set<std::string> s_used_names;
    static std::mutex                     s_mutex;

    static std::string generate_unique_name();
};

}  // namespace robot_name
