#include "linked_list.h"

namespace linked_list {

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), num_elements(0) {}

template <typename T>
List<T>::~List() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void List<T>::push(const T& value) {
    Node* new_node = new Node(value);
    if (!tail) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    num_elements++;
}

template <typename T>
T List<T>::pop() {
    // Assume the list is not empty as per tests
    Node* temp = tail;
    T value = temp->value;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    num_elements--;
    return value;
}

template <typename T>
T List<T>::shift() {
    // Assume the list is not empty as per tests
    Node* temp = head;
    T value = temp->value;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    num_elements--;
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* new_node = new Node(value);
    if (!head) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    num_elements++;
}

template <typename T>
int List<T>::count() const {
    return num_elements;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current) {
        if (current->value == value) {
            // Found the node to erase
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            num_elements--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit instantiations for all possible numeric types
template class List<int>;
template class List<long>;
template class List<long long>;
template class List<unsigned int>;
template class List<unsigned long>;
template class List<unsigned long long>;
template class List<short>;
template class List<unsigned short>;
template class List<char>;
template class List<signed char>;
template class List<unsigned char>;
template class List<bool>;
template class List<float>;
template class List<double>;
template class List<long double>;
template class List<wchar_t>;
template class List<char16_t>;
template class List<char32_t>;

// Add a struct that could represent a station
struct Station {
    int number;
    bool operator==(const Station& other) const {
        return number == other.number;
    }
};
template class List<Station>;
// Add other types if necessary

}  // namespace linked_list
