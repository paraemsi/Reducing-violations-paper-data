#pragma once

#include <cstdint>
#include <cstddef>

namespace linked_list {

using station_id_t = std::int32_t;

template <typename T>
class List
{
private:
    struct Node
    {
        T value;
        Node* prev;
        Node* next;
        /* explicit removed for aggregate initialization compatibility */
        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t sz;

public:
    List() : head(nullptr), tail(nullptr), sz(0U) {}

    ~List()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        sz = 0U;
    }

    void push(const T& value)
    {
        Node* node = new Node(value);
        if (tail == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        sz = (sz + 1U);
    }

    T pop()
    {
        if (tail == nullptr)
        {
            throw "pop from empty list";
        }
        Node* node = tail;
        T value = node->value;
        if (tail->prev != nullptr)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
            tail = nullptr;
        }
        delete node;
        sz = (sz - 1U);
        return value;
    }

    void unshift(const T& value)
    {
        Node* node = new Node(value);
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }
        sz = (sz + 1U);
    }

    T shift()
    {
        if (head == nullptr)
        {
            throw "shift from empty list";
        }
        Node* node = head;
        T value = node->value;
        if (head->next != nullptr)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
        {
            head = nullptr;
            tail = nullptr;
        }
        delete node;
        sz = (sz - 1U);
        return value;
    }

    std::size_t count() const
    {
        return sz;
    }

    bool erase(const T& value)
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            if (curr->value == value)
            {
                if (curr->prev != nullptr)
                {
                    curr->prev->next = curr->next;
                }
                else
                {
                    head = curr->next;
                }
                if (curr->next != nullptr)
                {
                    curr->next->prev = curr->prev;
                }
                else
                {
                    tail = curr->prev;
                }
                delete curr;
                sz = (sz - 1U);
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // Disable copy
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // Allow move
    List(List&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0U;
    }
    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            while (head != nullptr)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = other.head;
            tail = other.tail;
            sz = other.sz;
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0U;
        }
        return *this;
    }
};

}  // namespace linked_list
