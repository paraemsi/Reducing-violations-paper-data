#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>
#include <mutex>

namespace robot_name {

class Robot {
public:
    Robot();
    ~Robot();

    // Disable copy and move semantics to guarantee each live robot
    // instance owns a unique name in the global registry.
    Robot(const Robot&) = delete;
    Robot(Robot&&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot& operator=(Robot&&) = delete;

    const std::string& name() const noexcept;
    void reset();

private:
    std::string _name;

    static std::string generate_unique_name();
    static std::unordered_set<std::string> used_names;
    static std::mt19937& rng();
    static std::mutex& mutex();
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
