#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <map>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& child) {
    std::vector<std::string> children = {"Alice", "Bob", "Charlie", "David", "Eve", "Fred", "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
    std::map<char, Plants> plant_map = {{'G', Plants::grass}, {'C', Plants::clover}, {'R', Plants::radishes}, {'V', Plants::violets}};

    // Parse diagram
    std::istringstream iss(diagram);
    std::string row1, row2;
    std::getline(iss, row1);
    std::getline(iss, row2);

    if (row1.size() != 12 || row2.size() != 12) {
        throw std::invalid_argument("Invalid garden diagram");
    }

    // Find child index
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end()) {
        throw std::invalid_argument("Unknown child");
    }
    int index = it - children.begin();

    // Get plants
    std::array<Plants, 4> result;
    result[0] = plant_map.at(row1[2 * index]);
    result[1] = plant_map.at(row1[2 * index + 1]);
    result[2] = plant_map.at(row2[2 * index]);
    result[3] = plant_map.at(row2[2 * index + 1]);
    return result;
}

}  // namespace kindergarten_garden
