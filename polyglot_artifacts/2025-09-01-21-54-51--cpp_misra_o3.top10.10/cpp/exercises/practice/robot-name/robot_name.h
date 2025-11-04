#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot() = default;

    /* robots are unique and should not be copied or moved */
    robot(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(const robot&) = delete;
    robot& operator=(robot&&) = delete;

    ~robot();

    /* Return the robot’s current name, generating one on first call */
    const std::string& name() const;

    /* Reset the robot to factory settings (name cleared) */
    void reset();

private:
    mutable std::string name_;

    /* Generate a new unique robot name */
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
