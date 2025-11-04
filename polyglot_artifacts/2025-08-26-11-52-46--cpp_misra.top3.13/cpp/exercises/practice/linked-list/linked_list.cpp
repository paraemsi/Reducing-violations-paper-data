#include "linked_list.h"

namespace linked_list {

template <typename T>
void List<T>::push(const T& value) {
    Node* node = new Node(value);
    if (tail == nullptr) {
        head = node;
        tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    sz = (sz + 1U);
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        // List is empty, throw or handle as needed
        throw "pop from empty list";
    }
    Node* node = tail;
    T value = node->value;
    if (tail->prev != nullptr) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete node;
    sz = (sz - 1U);
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    sz = (sz + 1U);
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        // List is empty, throw or handle as needed
        throw "shift from empty list";
    }
    Node* node = head;
    T value = node->value;
    if (head->next != nullptr) {
        head = head->next;
        head->prev = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete node;
    sz = (sz - 1U);
    return value;
}

template <typename T>
std::size_t List<T>::count() const {
    return sz;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if ((current->prev == nullptr) && (current->next == nullptr)) {
                // Only node
                head = nullptr;
                tail = nullptr;
            } else if (current->prev == nullptr) {
                // Head node
                head = current->next;
                head->prev = nullptr;
            } else if (current->next == nullptr) {
                // Tail node
                tail = current->prev;
                tail->next = nullptr;
            } else {
                // Middle node
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            sz = (sz - 1U);
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit template instantiation for station_id_t
// Remove explicit instantiation to avoid linker errors with templates in C++
// template class List<station_id_t>;

}  // namespace linked_list
