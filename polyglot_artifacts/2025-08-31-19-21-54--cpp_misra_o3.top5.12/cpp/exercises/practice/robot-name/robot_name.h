#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>
#include <mutex>

namespace robot_name {

class Robot
{
public:
    Robot();

    const std::string& name() const;

    void reset();

private:
    std::string m_name;

    static std::string generate_unique_name();
    static std::string generate_name_candidate();

    static std::unordered_set<std::string> s_used_names;
    static std::mt19937 s_rng;
    static std::mutex s_mutex;
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
