#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& student) {
    // List of children in fixed order
    vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    int index = distance(children.begin(), find(children.begin(), children.end(), student));
    
    // Split the diagram into two rows
    // The diagram may have newline characters
    size_t newline_pos = diagram.find('\n');
    string row1 = diagram.substr(0, newline_pos);
    string row2 = diagram.substr(newline_pos + 1);
    
    // Plant code to enum mapping
    map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Each child has 2 plants per row, at positions 2*index and 2*index +1
    vector<Plants> result;
    result.push_back(plant_map[row1[2 * index]]);
    result.push_back(plant_map[row1[2 * index + 1]]);
    result.push_back(plant_map[row2[2 * index]]);
    result.push_back(plant_map[row2[2 * index + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
