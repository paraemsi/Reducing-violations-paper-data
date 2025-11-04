#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();
    
    std::string name() const;
    void reset();
    
private:
    mutable std::string name_;
    static std::unordered_set<std::string> used_names_;
    
    std::string generate_unique_name() const;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
