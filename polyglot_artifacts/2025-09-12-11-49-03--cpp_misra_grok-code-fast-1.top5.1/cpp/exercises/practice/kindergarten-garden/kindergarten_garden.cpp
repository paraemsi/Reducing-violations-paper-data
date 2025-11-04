#include "kindergarten_garden.h"
#include <algorithm>

namespace kindergarten_garden {

Plants plant_name(char plant_code) {
    if ((plant_code == 'G')) {
        return Plants::grass;
    } else if ((plant_code == 'C')) {
        return Plants::clover;
    } else if ((plant_code == 'R')) {
        return Plants::radishes;
    } else if ((plant_code == 'V')) {
        return Plants::violets;
    } else {
        return Plants::grass;  // default
    }
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& child) {
    std::vector<std::string> children = {"Alice", "Bob", "Charlie", "David", "Eve", "Fred", "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
    std::vector<std::string>::const_iterator it = std::find(children.begin(), children.end(), child);
    if ((it == children.end())) {
        return {Plants::grass, Plants::grass, Plants::grass, Plants::grass};  // default
    }
    std::size_t index = static_cast<std::size_t>(it - children.begin());
    std::size_t newline_pos = diagram.find('\n');
    std::string row1;
    std::string row2;
    if ((newline_pos != std::string::npos)) {
        row1 = diagram.substr(0U, newline_pos);
        row2 = diagram.substr((newline_pos + 1U));
    } else {
        row1 = diagram;
        row2 = "";
    }
    std::size_t pos1 = (2U * index);
    std::size_t pos2 = (pos1 + 1U);
    std::array<Plants, 4> result;
    if (((pos2 < row1.size()) && (pos2 < row2.size()))) {
        result[0] = plant_name(row1[pos1]);
        result[1] = plant_name(row1[pos2]);
        result[2] = plant_name(row2[pos1]);
        result[3] = plant_name(row2[pos2]);
    } else {
        result = {Plants::grass, Plants::grass, Plants::grass, Plants::grass};
    }
    return result;
}

}  // namespace kindergarten_garden
