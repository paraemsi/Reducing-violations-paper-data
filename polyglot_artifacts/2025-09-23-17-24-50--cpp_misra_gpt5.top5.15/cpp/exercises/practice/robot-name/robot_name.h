#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot() noexcept;
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(robot&&) = delete;

    void reset();
    std::string name() const;

private:
    std::string m_name;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
