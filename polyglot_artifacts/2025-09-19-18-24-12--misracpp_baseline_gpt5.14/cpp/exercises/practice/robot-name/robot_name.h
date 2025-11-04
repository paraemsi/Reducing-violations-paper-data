#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot() = default;

    // Returns the robot's name, generating a unique one on first call.
    std::string name() const;

    // Resets the robot to factory settings. Its current name is released and cleared.
    void reset();

private:
    mutable std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
