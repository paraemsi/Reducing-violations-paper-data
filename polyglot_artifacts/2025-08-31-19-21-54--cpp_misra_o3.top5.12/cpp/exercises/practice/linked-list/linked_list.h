#pragma once

#include <cstddef>      // for std::size_t
#include <cstdint>      // fixed-width integer types (MISRA rule requirement)
#include <stdexcept>    // for std::out_of_range
#include <utility>      // for std::move

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        T     value;
        Node* prev;
        Node* next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node*       m_head;
    Node*       m_tail;
    std::size_t m_size;

    // helper to delete a node safely
    static void delete_node(Node* node)
    {
        delete node;
    }

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(0U) {}

    // disable copy semantics to keep ownership simple
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    // enable move semantics
    List(List&& other) noexcept :
        m_head(other.m_head),
        m_tail(other.m_tail),
        m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            m_head       = other.m_head;
            m_tail       = other.m_tail;
            m_size       = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0U;
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* new_node = new Node(value);
        if (m_tail == nullptr)
        {
            // list is empty
            m_head = new_node;
            m_tail = new_node;
        }
        else
        {
            new_node->prev = m_tail;
            m_tail->next   = new_node;
            m_tail         = new_node;
        }
        ++m_size;
    }

    T pop()
    {
        if (m_tail == nullptr)
        {
            throw std::out_of_range("pop on empty list");
        }

        Node*       node_to_remove = m_tail;
        T           ret            = std::move(node_to_remove->value);
        m_tail                     = node_to_remove->prev;

        if (m_tail != nullptr)
        {
            m_tail->next = nullptr;
        }
        else
        {
            // list became empty
            m_head = nullptr;
        }

        delete_node(node_to_remove);
        --m_size;
        return ret;
    }

    void unshift(const T& value)
    {
        Node* new_node = new Node(value);
        if (m_head == nullptr)
        {
            // list is empty
            m_head = new_node;
            m_tail = new_node;
        }
        else
        {
            new_node->next = m_head;
            m_head->prev   = new_node;
            m_head         = new_node;
        }
        ++m_size;
    }

    T shift()
    {
        if (m_head == nullptr)
        {
            throw std::out_of_range("shift on empty list");
        }

        Node*       node_to_remove = m_head;
        T           ret            = std::move(node_to_remove->value);
        m_head                     = node_to_remove->next;

        if (m_head != nullptr)
        {
            m_head->prev = nullptr;
        }
        else
        {
            // list became empty
            m_tail = nullptr;
        }

        delete_node(node_to_remove);
        --m_size;
        return ret;
    }

    std::size_t count() const noexcept
    {
        return m_size;
    }

    bool erase(const T& value)
    {
        Node* current = m_head;
        while (current != nullptr)
        {
            if (current->value == value)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    // removing head
                    m_head = current->next;
                }

                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                else
                {
                    // removing tail
                    m_tail = current->prev;
                }

                delete_node(current);
                --m_size;
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    void clear()
    {
        while (m_head != nullptr)
        {
            Node* tmp = m_head;
            m_head    = m_head->next;
            delete_node(tmp);
        }
        m_tail = nullptr;
        m_size = 0U;
    }
};

}  // namespace linked_list
