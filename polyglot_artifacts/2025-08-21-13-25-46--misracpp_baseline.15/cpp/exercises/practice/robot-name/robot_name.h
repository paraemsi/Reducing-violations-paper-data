#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    const std::string& name();
    void reset();

private:
    mutable std::string m_name;
    void generate_name() const;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
