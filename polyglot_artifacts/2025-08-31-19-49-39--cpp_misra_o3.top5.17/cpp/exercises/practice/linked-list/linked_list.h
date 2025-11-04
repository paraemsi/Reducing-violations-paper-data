#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        T               data {};
        Node*           prev {nullptr};
        Node*           next {nullptr};
    };

    Node*              head_ {nullptr};
    Node*              tail_ {nullptr};
    std::uint64_t      size_ {0U};

    /* helper : delete a single node */
    static void delete_node(Node* node_ptr)
    {
        if(node_ptr != nullptr)
        {
            delete node_ptr;
        }
    }

public:
    List() = default;

    /* copy constructor */
    List(const List& other) :
        head_(nullptr),
        tail_(nullptr),
        size_(0U)
    {
        Node* current {(other.head_)};
        while(current != nullptr)
        {
            push(current->data);
            current = current->next;
        }
    }

    /* copy assignment */
    List& operator=(const List& other)
    {
        if(this != &other)
        {
            clear();
            Node* current {(other.head_)};
            while(current != nullptr)
            {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    /* enable move semantics */
    List(List&& other) noexcept :
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if(this != &other)
        {
            clear();
            head_       = other.head_;
            tail_       = other.tail_;
            size_       = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    /* return element count */
    std::uint64_t count() const noexcept
    {
        return size_;
    }

    /* add element to end */
    void push(const T& value)
    {
        Node* const new_node {new Node{value, tail_, nullptr}};
        if(tail_ == nullptr)
        {
            head_ = new_node;
        }
        else
        {
            tail_->next = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    /* remove and return last element */
    T pop()
    {
        if(tail_ == nullptr)
        {
            throw std::out_of_range("pop from empty list");
        }

        Node* const node_to_remove {tail_};
        if(tail_->prev == nullptr)
        {
            /* only one element */
            head_ = nullptr;
            tail_ = nullptr;
        }
        else
        {
            tail_         = tail_->prev;
            tail_->next   = nullptr;
        }
        --size_;
        T value {node_to_remove->data};
        delete_node(node_to_remove);
        return value;
    }

    /* add element to front */
    void unshift(const T& value)
    {
        Node* const new_node {new Node{value, nullptr, head_}};
        if(head_ == nullptr)
        {
            tail_ = new_node;
        }
        else
        {
            head_->prev = new_node;
        }
        head_ = new_node;
        ++size_;
    }

    /* remove and return first element */
    T shift()
    {
        if(head_ == nullptr)
        {
            throw std::out_of_range("shift from empty list");
        }

        Node* const node_to_remove {head_};
        if(head_->next == nullptr)
        {
            /* only one element */
            head_ = nullptr;
            tail_ = nullptr;
        }
        else
        {
            head_         = head_->next;
            head_->prev   = nullptr;
        }
        --size_;
        T value {node_to_remove->data};
        delete_node(node_to_remove);
        return value;
    }

    /* erase first occurrence of value */
    bool erase(const T& value)
    {
        Node* current {head_};

        while(current != nullptr)
        {
            if(current->data == value)
            {
                if(current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    head_ = current->next;
                }

                if(current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                else
                {
                    tail_ = current->prev;
                }

                delete_node(current);
                --size_;
                return true; /* first occurrence removed */
            }
            current = current->next;
        }
        return false;
    }

private:
    void clear() noexcept
    {
        Node* current {head_};
        while(current != nullptr)
        {
            Node* const next_node {current->next};
            delete_node(current);
            current = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }
};

}  // namespace linked_list
