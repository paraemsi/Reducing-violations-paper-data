#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class Robot {
public:
    Robot();
    ~Robot() = default;

    // Returns the robot's name, generating it if necessary
    std::string name();

    // Resets the robot to factory settings (wipes the name)
    void reset();

private:
    std::string m_name;
    void generate_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
