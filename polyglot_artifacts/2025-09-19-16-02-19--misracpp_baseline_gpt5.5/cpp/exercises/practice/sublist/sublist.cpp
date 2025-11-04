#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    return classify(a, b);
}

List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return classify(a, b);
}

List_comparison sublist(const std::vector<int>& a, std::initializer_list<int> b) {
    return classify(a, b);
}

List_comparison sublist(std::initializer_list<int> a, const std::vector<int>& b) {
    return classify(a, b);
}

}  // namespace sublist
