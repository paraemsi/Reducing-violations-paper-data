#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

namespace kindergarten_garden {

    vector<Plants> plants(const string& diagram, const string& child) {
        // Split the diagram into lines
        istringstream iss(diagram);
        vector<string> rows;
        string line;
        while (getline(iss, line)) {
            // Trim any trailing carriage return (for cross-platform compatibility)
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                rows.push_back(line);
            }
        }
        
        // We should have exactly two non-empty rows
        if (rows.size() < 2) {
            return {};
        }
        
        const string& first_row = rows[0];
        const string& second_row = rows[1];
        
        // List of children in fixed order
        vector<string> children = {
            "Alice", "Bob", "Charlie", "David",
            "Eve", "Fred", "Ginny", "Harriet",
            "Ileana", "Joseph", "Kincaid", "Larry"
        };
        
        // Find the index of the child
        int index = -1;
        for (int i = 0; i < children.size(); i++) {
            if (children[i] == child) {
                index = i;
                break;
            }
        }
        
        if (index == -1) {
            return {};
        }
        
        // Calculate starting position for the child's plants
        int start_pos = 2 * index;
        
        // Check if positions are valid
        if (start_pos + 1 >= first_row.size() || start_pos + 1 >= second_row.size()) {
            return {};
        }
        
        // Get plants from both rows in order
        vector<Plants> result;
        // Process first two plants from the first row
        for (int i = 0; i < 2; i++) {
            char code = first_row[start_pos + i];
            switch (code) {
                case 'G': result.push_back(Plants::grass); break;
                case 'C': result.push_back(Plants::clover); break;
                case 'R': result.push_back(Plants::radishes); break;
                case 'V': result.push_back(Plants::violets); break;
                default: ; // Handle unexpected codes if necessary
            }
        }
        // Process next two plants from the second row
        for (int i = 0; i < 2; i++) {
            char code = second_row[start_pos + i];
            switch (code) {
                case 'G': result.push_back(Plants::grass); break;
                case 'C': result.push_back(Plants::clover); break;
                case 'R': result.push_back(Plants::radishes); break;
                case 'V': result.push_back(Plants::violets); break;
                default: ; // Handle unexpected codes if necessary
            }
        }
        return result;
    }

}  // namespace kindergarten_garden
