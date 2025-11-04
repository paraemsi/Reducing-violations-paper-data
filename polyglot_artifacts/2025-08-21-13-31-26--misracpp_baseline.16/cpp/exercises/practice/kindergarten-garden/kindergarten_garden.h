#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plant {
    violets,
    radishes,
    clover,
    grass
};

using Plants = Plant;

/**
 * Standalone function for test compatibility.
 * This must use the type Plants (not Plant) in the signature,
 * but the implementation can use Plant internally.
 */
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

class Garden {
public:
    Garden(const std::string& diagram,
           const std::vector<std::string>& students = std::vector<std::string>{
               "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
               "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
           });

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> student_plants_;
    static Plants char_to_plant(char c);
};

}  // namespace kindergarten_garden
