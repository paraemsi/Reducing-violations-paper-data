#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <random>

namespace robot_name {

class robot final
{
public:
    robot();

    const std::string& name();
    void reset();

private:
    std::string m_name;

    static std::string generate_unique_name();
    static std::mt19937& generator();
};

} // namespace robot_name

#endif // ROBOT_NAME_H
