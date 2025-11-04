#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& student) {
    // List of children in order
    const vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    int index = -1;
    for (int i = 0; i < 12; i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    // Ensure we found the student
    if (index == -1) {
        return {};
    }
    
    // Split the diagram into rows
    size_t newline_pos = diagram.find('\n');
    string row1 = diagram.substr(0, newline_pos);
    string row2 = diagram.substr(newline_pos + 1);
    
    // Each child has 2 plants per row, so their start index is 2 * index
    int start = 2 * index;
    
    // Get the plants from both rows
    vector<Plants> result;
    
    // Map plant codes to enum values
    map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Add plants from first row
    result.push_back(plant_map[row1[start]]);
    result.push_back(plant_map[row1[start + 1]]);
    
    // Add plants from second row
    result.push_back(plant_map[row2[start]]);
    result.push_back(plant_map[row2[start + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
