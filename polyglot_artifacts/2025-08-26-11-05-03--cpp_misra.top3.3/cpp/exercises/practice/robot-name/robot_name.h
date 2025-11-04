#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    std::string name();
    void reset();

private:
    std::string m_name;
    static std::unordered_set<std::string> s_used_names;

    static std::string generate_unique_name();
    static std::string generate_random_name();
    static void release_name(const std::string& name);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
