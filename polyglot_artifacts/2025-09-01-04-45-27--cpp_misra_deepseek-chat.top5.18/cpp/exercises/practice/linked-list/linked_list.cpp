#include "linked_list.h"
#include <stdexcept>

namespace linked_list {

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0U) {}

template <typename T>
List<T>::~List() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void List<T>::push(const T& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size_++;
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    Node* temp = tail;
    T value = temp->value;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    size_--;
    return value;
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        throw std::runtime_error("Cannot shift from empty list");
    }
    Node* temp = head;
    T value = temp->value;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    size_--;
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size_++;
}

template <typename T>
std::uint32_t List<T>::count() const {
    return size_;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            size_--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit template instantiations
template class List<int>;
template class List<long>;
template class List<double>;
template class List<float>;
template class List<char>;
template class List<unsigned int>;
template class List<unsigned long>;
template class List<bool>;
// Add other types as needed for the tests

}  // namespace linked_list
