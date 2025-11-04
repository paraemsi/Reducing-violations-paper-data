#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <cstdint>
#include <set>
#include <string>

namespace robot_name {

class robot {
public:
    robot();
    std::string name() const;
    void reset();

private:
    mutable std::string name_;
    static std::set<std::string> used_names_;
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
