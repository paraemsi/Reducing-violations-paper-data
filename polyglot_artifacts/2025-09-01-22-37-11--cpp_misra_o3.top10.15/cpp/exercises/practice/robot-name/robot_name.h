#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot final
{
public:
    robot();
    const std::string& name() const noexcept;
    void reset();

private:
    std::string name_;
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
