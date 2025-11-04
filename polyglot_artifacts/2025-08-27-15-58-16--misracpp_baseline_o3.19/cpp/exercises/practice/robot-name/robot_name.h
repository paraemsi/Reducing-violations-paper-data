#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class Robot {
public:
    Robot();

    const std::string& name() const;
    void reset();

private:
    mutable std::string m_name;
    static std::string generate_unique_name();
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
