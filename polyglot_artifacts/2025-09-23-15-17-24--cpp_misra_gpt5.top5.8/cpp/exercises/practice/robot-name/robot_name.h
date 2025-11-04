#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    const std::string& name() const;
    void reset();

private:
    std::string m_name;
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
