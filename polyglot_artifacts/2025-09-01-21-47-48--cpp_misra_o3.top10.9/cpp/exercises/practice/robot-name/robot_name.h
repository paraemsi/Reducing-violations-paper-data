#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot final
{
public:
    robot();

    void reset();
    [[nodiscard]] std::string name() const;

private:
    static std::string generate_unique_name();

    std::string m_name;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
