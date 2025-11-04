#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plants {
    radishes,
    clover,
    grass,
    violets
};

class Garden {
public:
    Garden(const std::string& diagram,
           const std::vector<std::string>& students = std::vector<std::string>());

    std::vector<Plants> plants(const std::string& student) const;

private:
// Note: No change needed here, just keeping the block for clarity.
// Note: No change needed here, just keeping the block for clarity.
// Note: No change needed here, just keeping the block for clarity.
    std::map<std::string, std::vector<Plants> > student_plants_;
};

// Standalone function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
