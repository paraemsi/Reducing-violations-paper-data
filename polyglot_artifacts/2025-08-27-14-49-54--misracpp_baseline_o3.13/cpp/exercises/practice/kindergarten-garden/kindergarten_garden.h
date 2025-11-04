#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants { clover, grass, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {
                        "Alice",  "Bob",   "Charlie", "David",
                        "Eve",    "Fred",  "Ginny",   "Harriet",
                        "Ileana", "Joseph","Kincaid", "Larry"});

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> assignments_;
};

std::array<Plants, 4> plants(
    const std::string& diagram,
    const std::string& student,
    const std::vector<std::string>& students = {
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"});

}  // namespace kindergarten_garden
