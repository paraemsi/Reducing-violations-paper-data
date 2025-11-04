#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot() = default;
    robot(const robot& other);
    robot& operator=(const robot& other);

    // Lazily generates and returns the robot's unique name.
    // The name is generated on first call and persists until reset().
    const std::string& name() const;

    // Resets the robot to factory settings.
    // The current name is released and a new name will be generated
    // the next time name() is called.
    void reset();

private:
    // Mutable to allow lazy initialization inside a const name() method.
    mutable std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
