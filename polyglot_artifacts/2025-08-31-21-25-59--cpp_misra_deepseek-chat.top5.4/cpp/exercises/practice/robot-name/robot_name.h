#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot {
private:
    std::string name_;
    
public:
    robot();
    ~robot();
    std::string name() const;
    void reset();
    
    // Prevent copying to avoid issues with name uniqueness
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    
    // Implement moving to properly manage active_names
    robot(robot&& other) noexcept;
    robot& operator=(robot&& other) noexcept;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
