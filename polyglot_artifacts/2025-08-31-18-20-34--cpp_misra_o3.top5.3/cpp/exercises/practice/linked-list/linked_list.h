#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T               value;
        Node*           prev;
        Node*           next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v)      : value(std::move(v)), prev(nullptr), next(nullptr) {}
        Node(const Node&)            = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&)                 = delete;
        Node& operator=(Node&&)      = delete;
    };

    Node*           head_{nullptr};
    Node*           tail_{nullptr};
    std::uint32_t   size_{0U};

    void remove_node(Node* node)
    {
        if(node == nullptr) {
            return;
        }

        if(node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            /* node was head */
            head_ = node->next;
        }

        if(node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            /* node was tail */
            tail_ = node->prev;
        }

        delete node;
        --size_;
    }

public:
    List()  = default;
    ~List()
    {
        while(head_ != nullptr) {
            Node* const next_node{head_->next};
            delete head_;
            head_ = next_node;
        }
        size_ = 0U;    /* list is now empty */
    }

    /* Adds an element to the end of the list */
    void push(const T& value)
    {
        Node* const new_node{new Node(value)};
        new_node->prev = tail_;
        if(tail_ != nullptr) {
            tail_->next = new_node;
        } else {
            /* list was empty, new node becomes head as well */
            head_ = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    /* Removes and returns the last element of the list */
    T pop()
    {
        if(size_ == 0U) {
            throw std::out_of_range("pop on empty List");
        }

        Node* const node_to_remove{tail_};
        T           ret_value{node_to_remove->value};

        tail_ = node_to_remove->prev;
        if(tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            /* list is now empty */
            head_ = nullptr;
        }

        delete node_to_remove;
        --size_;
        return ret_value;
    }

    /* Removes and returns the first element of the list */
    T shift()
    {
        if(size_ == 0U) {
            throw std::out_of_range("shift on empty List");
        }

        Node* const node_to_remove{head_};
        T           ret_value{node_to_remove->value};

        head_ = node_to_remove->next;
        if(head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            /* list is now empty */
            tail_ = nullptr;
        }

        delete node_to_remove;
        --size_;
        return ret_value;
    }

    /* Adds an element to the start of the list */
    void unshift(const T& value)
    {
        Node* const new_node{new Node(value)};
        new_node->next = head_;
        if(head_ != nullptr) {
            head_->prev = new_node;
        } else {
            /* list was empty, new node becomes tail as well */
            tail_ = new_node;
        }
        head_ = new_node;
        ++size_;
    }

    /* Returns the total number of elements in the list */
    std::uint32_t count() const noexcept
    {
        return size_;
    }

    /* Removes the first occurrence of 'value' from the list.
       Returns true if an element was removed, false otherwise. */
    bool erase(const T& value)
    {
        Node* current{head_};
        while(current != nullptr) {
            if(current->value == value) {
                remove_node(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /* Disable copy semantics to avoid accidental shallow copies */
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    /* Enable move semantics */
    List(List&& other) noexcept
        : head_{other.head_}
        , tail_{other.tail_}
        , size_{other.size_}
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if(this != &other) {
            /* clear current contents */
            while(head_ != nullptr) {
                Node* const next_node{head_->next};
                delete head_;
                head_ = next_node;
            }

            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }
};

}  // namespace linked_list
