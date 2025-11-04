#pragma once

#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T               data;
        Node*           next;
        Node*           prev;

        explicit Node(const T& value) : data{value}, next{nullptr}, prev{nullptr} {}
    };

    Node*           head_{nullptr};
    Node*           tail_{nullptr};
    std::uint32_t   size_{0U};

    /* helper: deletes a single node */
    static void delete_node(Node* node_ptr)
    {
        delete node_ptr;
    }

public:
    List() = default;

    /* copy-constructor */
    List(const List& other) : List()
    {
        Node* current{other.head_};
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    /* move-constructor */
    List(List&& other) noexcept :
        head_{other.head_},
        tail_{other.tail_},
        size_{other.size_}
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    /* copy-assignment */
    List& operator=(const List& other)
    {
        if (this != &other) {
            /* clear existing */
            while (size_ > 0U) {
                (void)pop();
            }

            Node* current{other.head_};
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    /* move-assignment */
    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            /* clear existing */
            while (size_ > 0U) {
                (void)pop();
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

    ~List()
    {
        while (size_ > 0U) {
            (void)pop();
        }
    }

    /* adds an element to the end */
    void push(const T& value)
    {
        Node* new_node{new Node(value)};
        if (tail_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
        ++size_;
    }

    /* removes and returns the last element */
    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* node_to_remove{tail_};
        T     value{node_to_remove->data};

        tail_ = node_to_remove->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            /* list became empty */
            head_ = nullptr;
        }

        delete_node(node_to_remove);
        --size_;
        return value;
    }

    /* adds an element to the beginning */
    void unshift(const T& value)
    {
        Node* new_node{new Node(value)};
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->next = head_;
            head_->prev    = new_node;
            head_          = new_node;
        }
        ++size_;
    }

    /* removes and returns the first element */
    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* node_to_remove{head_};
        T     value{node_to_remove->data};

        head_ = node_to_remove->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            /* list became empty */
            tail_ = nullptr;
        }

        delete_node(node_to_remove);
        --size_;
        return value;
    }

    /* returns the total number of elements */
    std::uint32_t count() const noexcept
    {
        return size_;
    }

    /* removes the first occurrence of 'value'; returns true if removed */
    bool erase(const T& value)
    {
        Node* current{head_};
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    /* removing head */
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    /* removing tail */
                    tail_ = current->prev;
                }

                delete_node(current);
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
