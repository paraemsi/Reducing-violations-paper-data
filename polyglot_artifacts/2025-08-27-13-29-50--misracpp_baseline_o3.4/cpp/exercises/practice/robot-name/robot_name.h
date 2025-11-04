#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>

namespace robot_name {

class Robot {
public:
    Robot() = default;

    // Return the robot's current name, generating it if necessary.
    std::string name() const;

    // Reset the robot to factory settings (clears its current name).
    void reset();

private:
    mutable std::string _name;  // Empty until first call to name()

    // Generate a unique robot name that does not collide with existing ones.
    static std::string generate_unique_name();

    // Registry of names currently in use.
    static std::unordered_set<std::string> used_names;
};

// Alias expected by test suite (lower-case `robot`)
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
