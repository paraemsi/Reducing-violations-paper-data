#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

namespace kindergarten_garden {

    vector<Plants> plants(const string& diagram, const string& student) {
        // Fixed list of children in order
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
        if (index == -1) return {};
        
        // Split the diagram into exactly two lines
        istringstream iss(diagram);
        string line1, line2;
        getline(iss, line1);
        getline(iss, line2);
        
        // Make sure to trim any carriage returns if present (for cross-platform compatibility)
        if (!line2.empty() && line2.back() == '\r') {
            line2.pop_back();
        }
        if (!line1.empty() && line1.back() == '\r') {
            line1.pop_back();
        }
        
        vector<Plants> result;
        
        // Process first line
        int pos = index * 2;
        for (int i = pos; i < pos + 2; i++) {
            switch (line1[i]) {
                case 'G': result.push_back(Plants::grass); break;
                case 'C': result.push_back(Plants::clover); break;
                case 'R': result.push_back(Plants::radishes); break;
                case 'V': result.push_back(Plants::violets); break;
            }
        }
        
        // Process second line
        for (int i = pos; i < pos + 2; i++) {
            switch (line2[i]) {
                case 'G': result.push_back(Plants::grass); break;
                case 'C': result.push_back(Plants::clover); break;
                case 'R': result.push_back(Plants::radishes); break;
                case 'V': result.push_back(Plants::violets); break;
            }
        }
        
        return result;
    }

}  // namespace kindergarten_garden
