#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

namespace {
    // Map a single diagram character to a plant enum.
    // Only equality comparisons with character literals are used, per rules.
    plant char_to_plant(const char ch) {
        if (ch == 'G') {
            return plant::grass;
        } else if (ch == 'C') {
            return plant::clover;
        } else if (ch == 'R') {
            return plant::radishes;
        } else if (ch == 'V') {
            return plant::violets;
        } else {
            throw std::invalid_argument("Unknown plant code in diagram");
        }
    }

    // Split the input diagram into two rows separated by a single newline.
    void split_rows(const std::string& diagram, std::string& row1, std::string& row2) {
        const std::string::size_type pos = diagram.find('\n');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Diagram must contain exactly two rows separated by a newline");
        }

        row1 = diagram.substr(std::string::size_type{0}, pos);
        row2 = diagram.substr(pos + std::string::size_type{1});

        if (row1.size() != row2.size()) {
            throw std::invalid_argument("Both diagram rows must be the same length");
        }
        if (((row1.size() % std::string::size_type{2}) != std::string::size_type{0})) {
            throw std::invalid_argument("Each row length must be an even number");
        }
    }
}  // namespace

std::vector<std::string> garden::default_students() {
    return std::vector<std::string>{
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Eve",
        "Fred",
        "Ginny",
        "Harriet",
        "Ileana",
        "Joseph",
        "Kincaid",
        "Larry"
    };
}

garden::garden(const std::string& diagram)
    : m_row1(), m_row2(), m_students(default_students()) {
    split_rows(diagram, m_row1, m_row2);
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : m_row1(), m_row2(), m_students(students) {
    split_rows(diagram, m_row1, m_row2);
    std::sort(m_students.begin(), m_students.end());
}

std::vector<plant> garden::plants(const std::string& student) const {
    // Find student's index without relying on signed/unsigned conversions.
    std::string::size_type idx = std::string::size_type{0};
    bool found = false;
    for (const auto& name : m_students) {
        if (name == student) {
            found = true;
            break;
        } else {
            idx = (idx + std::string::size_type{1});
        }
    }

    if (!found) {
        return std::vector<plant>{};
    }

    const std::string::size_type start = (idx * std::string::size_type{2});
    if (((m_row1.size() < (start + std::string::size_type{2}))) || ((m_row2.size() < (start + std::string::size_type{2})))) {
        throw std::out_of_range("Garden diagram too small for the requested student");
    }

    std::vector<plant> result{};
    result.reserve(std::vector<plant>::size_type{4});
    result.push_back(char_to_plant(m_row1.at(start)));
    result.push_back(char_to_plant(m_row1.at(start + std::string::size_type{1})));
    result.push_back(char_to_plant(m_row2.at(start)));
    result.push_back(char_to_plant(m_row2.at(start + std::string::size_type{1})));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    const std::vector<plant> vec = g.plants(student);
    if (vec.size() != std::vector<plant>::size_type{4}) {
        throw std::out_of_range("Student not found or diagram invalid");
    }
    std::array<Plants, 4> arr{
        vec.at(std::vector<plant>::size_type{0}),
        vec.at(std::vector<plant>::size_type{1}),
        vec.at(std::vector<plant>::size_type{2}),
        vec.at(std::vector<plant>::size_type{3})
    };
    return arr;
}

}  // namespace kindergarten_garden
