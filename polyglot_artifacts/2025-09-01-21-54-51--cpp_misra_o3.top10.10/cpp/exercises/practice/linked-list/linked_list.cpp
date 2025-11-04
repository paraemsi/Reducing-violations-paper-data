#include "linked_list.h"
#include <string>

namespace linked_list {

template <typename T>
void List<T>::push(const T& value)
{
    Node* const new_node = new Node(value);
    if (m_tail == nullptr) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        new_node->prev = m_tail;
        m_tail->next   = new_node;
        m_tail         = new_node;
    }
    ++m_size;
}

template <typename T>
T List<T>::pop()
{
    if (m_tail == nullptr) {
        throw std::out_of_range("pop on empty list");
    }
    Node* const node_to_remove = m_tail;
    const T     ret_val        = node_to_remove->value;

    m_tail = node_to_remove->prev;
    if (m_tail != nullptr) {
        m_tail->next = nullptr;
    } else {
        m_head = nullptr;
    }

    delete node_to_remove;
    --m_size;
    return ret_val;
}

template <typename T>
T List<T>::shift()
{
    if (m_head == nullptr) {
        throw std::out_of_range("shift on empty list");
    }
    Node* const node_to_remove = m_head;
    const T     ret_val        = node_to_remove->value;

    m_head = node_to_remove->next;
    if (m_head != nullptr) {
        m_head->prev = nullptr;
    } else {
        m_tail = nullptr;
    }

    delete node_to_remove;
    --m_size;
    return ret_val;
}

template <typename T>
void List<T>::unshift(const T& value)
{
    Node* const new_node = new Node(value);
    if (m_head == nullptr) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        new_node->next = m_head;
        m_head->prev   = new_node;
        m_head         = new_node;
    }
    ++m_size;
}

template <typename T>
bool List<T>::erase(const T& value)
{
    for (Node* current = m_head; current != nullptr; current = current->next) {
        if (current->value == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                m_head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                m_tail = current->prev;
            }

            delete current;
            --m_size;
            return true;
        }
    }
    return false;
}

template <typename T>
void List<T>::clear() noexcept
{
    Node* current = m_head;
    while (current != nullptr) {
        Node* const next_node = current->next;
        delete current;
        current = next_node;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0U;
}

// Explicit template instantiation for the types likely used in tests
template class List<int>;

}  // namespace linked_list
