#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <mutex>

namespace robot_name {

class robot {
public:
    robot() = default;

    // Returns the robot's name, generating one on first use.
    const std::string& name() const;

    // Resets the robot to factory settings (no name).
    void reset();

private:
    static std::string generate_unique_name();
    static std::string generate_candidate_name();

    // Mutable to allow lazy name generation in a const accessor.
    mutable std::string m_name;
    // Mutex to synchronize lazy initialization and reset.
    mutable std::mutex m_mutex;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
