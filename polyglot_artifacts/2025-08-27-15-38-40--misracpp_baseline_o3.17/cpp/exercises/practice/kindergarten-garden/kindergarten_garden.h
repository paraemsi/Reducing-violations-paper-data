#pragma once

#include <string>
#include <vector>
#include <array>
#include <unordered_map>

namespace kindergarten_garden {

enum class Plant { clover, grass, radishes, violets };

using Plants = Plant;

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = { "Alice",  "Bob",   "Charlie", "David",
                                                                "Eve",    "Fred",  "Ginny",   "Harriet",
                                                                "Ileana", "Joseph","Kincaid", "Larry" });

    std::vector<Plant> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<Plant>> m_plants;
    static Plant char_to_plant(char c);
};

// Free helper function to obtain a student's plants without
// explicitly constructing a garden instance.
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

}  // namespace kindergarten_garden
