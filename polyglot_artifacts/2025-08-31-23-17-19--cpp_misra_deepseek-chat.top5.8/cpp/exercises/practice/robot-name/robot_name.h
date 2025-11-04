#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>
#include <set>

namespace robot_name {

class robot {
private:
    std::string name_;
    static std::string generate_name();
    static std::set<std::string> used_names;
public:
    robot();
    std::string name() const;
    void reset();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
