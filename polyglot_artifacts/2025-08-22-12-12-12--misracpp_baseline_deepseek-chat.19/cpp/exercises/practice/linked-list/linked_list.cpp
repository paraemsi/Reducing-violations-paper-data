#include "linked_list.h"
#include <stdexcept>
#include <string>

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
    if (!tail) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    Node* temp = tail;
    T value = temp->value;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    num_elements--;
    return value;
}

template <typename T>
T List<T>::shift() {
    if (!head) {
        throw std::runtime_error("Cannot shift from empty list");
    }
    Node* temp = head;
    T value = temp->value;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
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
            // Adjust surrounding nodes' pointers
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                // This node is the head
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                // This node is the tail
                tail = current->prev;
            }
            // Delete the node and update count
            delete current;
            num_elements--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit template instantiation for common types
template class List<int>;
template class List<unsigned int>;
template class List<long>;
template class List<unsigned long>;
template class List<long long>;
template class List<unsigned long long>;
template class List<float>;
template class List<double>;
template class List<char>;
template class List<bool>;
template class List<std::string>;
// Add other types if necessary

}  // namespace linked_list
