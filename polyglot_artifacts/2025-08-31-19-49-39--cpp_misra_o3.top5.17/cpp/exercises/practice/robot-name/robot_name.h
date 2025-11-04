#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();

    // Return the robot's current name; generate one if none exists.
    std::string const & name();          // may allocate if none exists
    std::string const & name() const;    // guaranteed not to modify object

    // Reset to factory settings (name cleared – a new one will be generated on next call).
    void reset();

private:
    std::string m_name;

    // Create a new unique robot name.
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
