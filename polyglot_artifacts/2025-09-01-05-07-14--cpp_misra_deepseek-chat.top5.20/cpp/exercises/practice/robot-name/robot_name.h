#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
private:
    mutable std::string name_;
public:
    robot();
    ~robot();
    std::string name() const;
    void reset();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
