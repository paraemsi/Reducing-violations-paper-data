#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H
#include <string>

namespace robot_name {

class robot final
{
public:
    robot();
    ~robot();
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(robot&&) = delete;
    const std::string& name() const;
    void reset();

private:
    mutable std::string m_name;
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
