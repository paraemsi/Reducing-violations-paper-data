#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class Robot {
public:
    Robot();
    Robot(const Robot&) = delete;
    Robot(Robot&&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot& operator=(Robot&&) = delete;
    ~Robot() = default;

    const std::string& name();
    void reset();

private:
    std::string m_name;
    static std::string generate_unique_name();
};

using robot = Robot; /* alias expected by unit-tests */

}  // namespace robot_name

#endif // ROBOT_NAME_H
