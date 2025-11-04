#include "linked_list.h"
#include <stdexcept>

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
        throw std::out_of_range("pop from empty list");
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
        throw std::out_of_range("shift from empty list");
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
            if ((current->prev != nullptr) && (current->next != nullptr)) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            } else if (current->prev == nullptr) {
                // head
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (current->next == nullptr) {
                // tail
                tail = current->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            }
            delete current;
            sz = (sz - 1U);
            if (sz == 0U) {
                head = nullptr;
                tail = nullptr;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit template instantiation for station_id_t

// Move explicit instantiation outside the namespace to avoid linker errors

}  // namespace linked_list

// Explicit template instantiation for station_id_t
template class linked_list::List<linked_list::station_id_t>;
