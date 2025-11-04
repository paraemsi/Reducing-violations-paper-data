#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>

namespace robot_name {

class Robot {
public:
    Robot();
    ~Robot();

    // Non-copyable / non-movable to guarantee unique names
    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot(Robot&&) = delete;
    Robot& operator=(Robot&&) = delete;

    const std::string& name() const;   // Retrieve (or lazily create) the robot's name
    void reset();                // Reset to factory settings

private:
    mutable std::string name_;

    // Helpers
    static std::string generate_unique_name();
    static std::mt19937& rng();
    static std::unordered_set<std::string> used_names_;
};

// Provide the lowercase alias expected by the tests.
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
