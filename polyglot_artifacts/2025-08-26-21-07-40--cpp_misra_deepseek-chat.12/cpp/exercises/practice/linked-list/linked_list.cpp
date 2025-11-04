#include "linked_list.h"
#include <stdexcept>
#include <cstdint>

namespace linked_list {

template <typename T>
List<T>::~List() {
    typename List<T>::Node* current = head;
    while (current != nullptr) {
        typename List<T>::Node* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void List<T>::push(const T& value) {
    typename List<T>::Node* new_node = new Node(value);
    if (tail == nullptr) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    list_size++;
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    typename List<T>::Node* last_node = tail;
    T value = last_node->value;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete last_node;
    list_size--;
    return value;
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        throw std::runtime_error("Cannot shift from empty list");
    }
    typename List<T>::Node* first_node = head;
    T value = first_node->value;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete first_node;
    list_size--;
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    typename List<T>::Node* new_node = new Node(value);
    if (head == nullptr) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    list_size++;
}

template <typename T>
bool List<T>::erase(const T& value) {
    typename List<T>::Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            // Adjust the previous node's next pointer
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            // Adjust the next node's previous pointer
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            list_size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit instantiations
template class List<int>;
}  // namespace linked_list
