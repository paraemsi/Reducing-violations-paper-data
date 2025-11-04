#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <set>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    std::string name() const;
    void reset();
private:
    std::string robot_name;
    void generate_name();
    static std::set<std::string> used_names;
    static std::string generate_random_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
