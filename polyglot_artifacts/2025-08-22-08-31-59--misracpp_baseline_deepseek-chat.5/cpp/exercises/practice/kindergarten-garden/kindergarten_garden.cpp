#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& student) {
    // Fixed list of children in order
    vector<string> children = {
        "Alice", "Bob", "Charlie", "David", 
        "Eve", "Fred", "Ginny", "Harriet", 
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    int index = -1;
    for (int i = 0; i < static_cast<int>(children.size()); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into lines
    istringstream iss(diagram);
    string line1, line2;
    getline(iss, line1);
    getline(iss, line2);
    
    // Ensure the lines are long enough
    // Each child has 2 plants per row, and there are 12 children, so 24 plants per row
    // Make sure we don't access out of bounds
    int start_pos = 2 * index;
    
    // Map the plant codes to enum values
    map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Get all plants in the correct order
    vector<Plants> result;
    result.push_back(plant_map[line1[start_pos]]);
    result.push_back(plant_map[line1[start_pos + 1]]);
    result.push_back(plant_map[line2[start_pos]]);
    result.push_back(plant_map[line2[start_pos + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
