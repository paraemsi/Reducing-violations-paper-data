#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace robot_name {

class robot final
{
public:
    robot();
    std::string name() const;
    void reset();

private:
    std::string m_name;
    static std::unordered_set<std::string> s_usedNames;

    static std::string generateName();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
