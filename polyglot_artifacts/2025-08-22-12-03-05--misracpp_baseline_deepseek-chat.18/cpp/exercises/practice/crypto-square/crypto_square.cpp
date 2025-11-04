#include "crypto_square.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <functional>
#include <stdexcept>
#include <sstream>
using namespace std;

namespace crypto_square {

cipher::cipher(const string& text) {
    for (char c : text) {
        if (isalnum(c)) {
            normalized += tolower(c);
        }
    }
}

string cipher::normalize_plain_text() const {
    return normalized;
}

vector<string> cipher::plain_text_segments() const {
    size_t length = normalized.length();
    if (length == 0) return {};
    
    // Determine number of columns and rows
    size_t c = 0;
    size_t r = 0;
    // Start from the ceiling of the square root
    c = static_cast<size_t>(ceil(sqrt(length)));
    while (true) {
        r = (length + c - 1) / c; // Ceiling division
        if (c >= r && (c - r) <= 1) {
            break;
        }
        c++;
    }
    
    // Split into r rows of c characters each
    vector<string> segments;
    for (size_t i = 0; i < r; i++) {
        size_t start = i * c;
        if (start < length) {
            size_t end = min(start + c, length);
            segments.push_back(normalized.substr(start, end - start));
        }
    }
    return segments;
}

string cipher::cipher_text() const {
    size_t length = normalized.length();
    if (length == 0) return "";
    
    // Get the plain text segments
    auto segments = plain_text_segments();
    size_t r = segments.size();
    size_t c = (r > 0) ? segments[0].size() : 0;
    
    // Pad each segment to exactly c characters with spaces
    for (auto& segment : segments) {
        if (segment.size() < c) {
            segment.append(c - segment.size(), ' ');
        }
    }
    
    // Read down the columns
    string result;
    for (size_t i = 0; i < c; i++) {
        for (size_t j = 0; j < r; j++) {
            result += segments[j][i];
        }
    }
    return result;
}

string cipher::normalized_cipher_text() const {
    string ct = cipher_text();
    if (ct.empty()) return "";
    
    // Get number of rows and columns from plain_text_segments
    auto segments = plain_text_segments();
    size_t r = segments.size();
    
    // Split into chunks of r length, separated by spaces
    string result;
    for (size_t i = 0; i < ct.size(); i += r) {
        if (i != 0) {
            result += ' ';
        }
        // Get a substring of length r
        result += ct.substr(i, r);
    }
    return result;
}

}  // namespace crypto_square
