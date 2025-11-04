#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& student) {
    // Fixed order of children
    const vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    int index = 0;
    for (int i = 0; i < 12; i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into lines, ignoring empty lines
    vector<string> rows;
    istringstream iss(diagram);
    string line;
    while (getline(iss, line)) {
        if (!line.empty()) {
            rows.push_back(line);
        }
    }
    
    // We should have exactly two rows
    // Each row should have at least 2*(index +1) characters
    vector<Plants> result;
    
    // Process first row
    const string& row1 = rows[0];
    for (int i = 2 * index; i < 2 * index + 2; i++) {
        switch (row1[i]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
        }
    }
    
    // Process second row
    const string& row2 = rows[1];
    for (int i = 2 * index; i < 2 * index + 2; i++) {
        switch (row2[i]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
