#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace robot_name {

using robot_name_string = std::string;

class robot {
public:
    robot();
    ~robot();

    robot_name_string name();
    void reset();

private:
    robot_name_string m_name;
    static std::unordered_set<robot_name_string>& s_used_names();

    static robot_name_string generate_unique_name();
    static robot_name_string generate_random_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
