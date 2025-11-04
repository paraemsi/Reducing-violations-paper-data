#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot() = default;

    // Returns the robot's name, generating one if needed
    std::string name() const;

    // Resets the robot to factory settings (wipes name)
    void reset();

private:
    std::string m_name;
    void generate_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
