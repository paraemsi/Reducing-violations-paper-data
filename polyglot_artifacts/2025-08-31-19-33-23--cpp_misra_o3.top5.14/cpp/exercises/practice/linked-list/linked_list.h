#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    /* node of the doubly-linked list */
    struct Node {
        T     value;
        Node* prev;
        Node* next;

        Node(const T& v, Node* p, Node* n) : value(v), prev(p), next(n) {}
    };
    
public:
    using size_type = std::uint32_t;

    List() = default;

    /* non-copyable, non-movable for simplicity */
    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&)            = delete;
    List& operator=(List&&) = delete;

    ~List() noexcept
    {
        clear();
    }

    /* add element to back */
    void push(const T& value)
    {
        Node* const new_node = new Node(value, tail_, nullptr);
        if((head_ == nullptr)) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next = new_node;
            tail_       = new_node;
        }
        ++size_;
    }

    /* remove element from back and return it */
    T pop()
    {
        if(size_ == static_cast<size_type>(0)) {
            throw std::out_of_range("pop on empty list");
        }

        Node* const node_to_remove = tail_;
        const T     return_value   = node_to_remove->value;

        tail_ = node_to_remove->prev;
        if((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node_to_remove;
        --size_;
        return return_value;
    }

    /* add element to front */
    void unshift(const T& value)
    {
        Node* const new_node = new Node(value, nullptr, head_);
        if((head_ == nullptr)) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            head_->prev = new_node;
            head_       = new_node;
        }
        ++size_;
    }

    /* remove element from front and return it */
    T shift()
    {
        if(size_ == static_cast<size_type>(0)) {
            throw std::out_of_range("shift on empty list");
        }

        Node* const node_to_remove = head_;
        const T     return_value   = node_to_remove->value;

        head_ = node_to_remove->next;
        if((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node_to_remove;
        --size_;
        return return_value;
    }

    /* remove first occurrence of value; return true if removed */
    bool erase(const T& value)
    {
        Node* current = head_;
        while(current != nullptr) {
            if(current->value == value) {
                remove_node(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /* number of elements in the list */
    size_type count() const noexcept
    {
        return size_;
    }


    Node*      head_ { nullptr };
    Node*      tail_ { nullptr };
    size_type  size_ { static_cast<size_type>(0) };

    void clear() noexcept
    {
        Node* current = head_;
        while(current != nullptr) {
            Node* const next_node = current->next;
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<size_type>(0);
    }

    void remove_node(Node* node)
    {
        if(node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }

        if(node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }

        delete node;
        --size_;
    }
};

}  // namespace linked_list
