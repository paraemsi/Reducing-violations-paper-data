#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <mutex>

namespace robot_name {

class Robot final {
public:
    Robot();

    // Returns the robot's name, generating a new one the first time it is called
    // after construction or a call to reset().
    const std::string& name() const;

    // Resets the robot to factory settings. The next call to name() will return
    // a freshly generated unique name.
    void reset();

private:
    mutable std::string m_name;
    mutable std::mutex  m_mutex;

    static std::string generate_unique_name();
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
