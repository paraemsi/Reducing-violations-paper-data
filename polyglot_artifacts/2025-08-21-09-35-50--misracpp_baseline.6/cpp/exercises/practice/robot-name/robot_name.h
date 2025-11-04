#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class Robot {
public:
    Robot();
    const std::string& name();
    void reset();

private:
    std::string m_name;
    void generate_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
