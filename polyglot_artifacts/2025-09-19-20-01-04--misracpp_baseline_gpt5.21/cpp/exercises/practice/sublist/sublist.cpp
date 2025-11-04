#include "sublist.h"

namespace sublist {

comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    return compare(a, b);
}

comparison classify(const std::vector<int>& a, const std::vector<int>& b) {
    return compare(a, b);
}

comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return compare(std::vector<int>(a), std::vector<int>(b));
}

comparison classify(std::initializer_list<int> a, std::initializer_list<int> b) {
    return compare(std::vector<int>(a), std::vector<int>(b));
}

}  // namespace sublist
