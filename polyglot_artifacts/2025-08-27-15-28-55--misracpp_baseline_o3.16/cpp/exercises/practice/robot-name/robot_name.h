#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class Robot {
public:
    Robot() = default;

    // Return the robot's name, generating one if necessary.
    const std::string& name() const;

    // Reset the robot to its factory settings (clears name).
    void reset();

private:
    mutable std::string name_;

    // Generate a guaranteed-unique name.
    static std::string generate_unique_name();
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
