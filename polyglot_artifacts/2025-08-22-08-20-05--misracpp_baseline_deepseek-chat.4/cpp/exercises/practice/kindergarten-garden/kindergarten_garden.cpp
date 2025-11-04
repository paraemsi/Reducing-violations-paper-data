#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return {};
    }
    
    // Split the diagram into two rows
    size_t newline_pos = diagram.find('\n');
    string row1 = diagram.substr(0, newline_pos);
    string row2 = diagram.substr(newline_pos + 1);
    
    // Each child gets two plants from each row
    int start_pos = 2 * index;
    vector<Plants> result;
    
    // Map plant codes to enum values
    static const map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Add plants from first row
    result.push_back(plant_map.at(row1[start_pos]));
    result.push_back(plant_map.at(row1[start_pos + 1]));
    
    // Add plants from second row
    result.push_back(plant_map.at(row2[start_pos]));
    result.push_back(plant_map.at(row2[start_pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
