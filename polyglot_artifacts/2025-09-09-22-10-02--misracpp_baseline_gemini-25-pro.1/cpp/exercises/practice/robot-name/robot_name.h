#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();
    const std::string& name() const;
    void reset();

    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
private:
    mutable std::string robot_name_;
    mutable std::string name_to_release_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
