#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& student) {
    const vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = find(children.begin(), children.end(), student);
    int index = distance(children.begin(), it);
    
    // Split into two lines
    istringstream iss(diagram);
    string line1, line2;
    getline(iss, line1);
    getline(iss, line2);
    
    // Ensure we have valid indices
    vector<Plants> result;
    result.reserve(4);
    
    // Get each plant
    int pos = 2 * index;
    for (int i = 0; i < 2; i++) {
        char c = line1[pos + i];
        switch (c) {
            case 'C': result.push_back(Plants::clover); break;
            case 'G': result.push_back(Plants::grass); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
        }
    }
    for (int i = 0; i < 2; i++) {
        char c = line2[pos + i];
        switch (c) {
            case 'C': result.push_back(Plants::clover); break;
            case 'G': result.push_back(Plants::grass); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
