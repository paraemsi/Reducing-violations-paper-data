#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <cstdint>
#include <string>

namespace robot_name {

class robot {
   public:
    robot();
    std::string const& name() const;
    void reset();

   private:
    std::string name_{};
};

}  // namespace robot_name

#endif  // ROBOT_NAME_H
