#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>

namespace robot_name {

class robot {
public:
    robot();                         // construct with a fresh unique name
    ~robot();                        // release the name when robot is destroyed

    // robots are unique entities – copying is forbidden, moving transfers ownership
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;

    robot(robot&&) noexcept;            // move-construct — transfers the unique name
    robot& operator=(robot&&) noexcept; // move-assign  — transfers the unique name

    const std::string& name() const; // obtain current name
    void reset();                    // reset to factory settings (new unique name)

private:
    std::string name_;                        // current robot name
    static std::string generate_unique_name(); // helper to create a unique id
    static std::unordered_set<std::string> allocated_; // names currently in use
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
