#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
private:
    std::string robot_name_;
public:
    robot();
    std::string name() const;
    void reset();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
