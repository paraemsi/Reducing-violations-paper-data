#pragma once

#include <cstddef>   // for std::size_t
#include <cstdint>   // fixed-width integer types
#include <stdexcept> // for std::out_of_range
#include <utility>   // for std::move

namespace linked_list {

template <typename T>
class List
{
public:
    List() noexcept = default;
    ~List();

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;

    void push(const T& value);  // add to back
    T    pop();                 // remove from back

    void unshift(const T& value); // add to front
    T    shift();                 // remove from front

    std::size_t count() const noexcept; // number of elements
    bool erase(const T& value);         // remove first occurrence

private:
    struct Node
    {
        explicit Node(const T& v) : data(v) {}
        explicit Node(T&& v) : data(std::move(v)) {}
        T     data;
        Node* prev{nullptr};
        Node* next{nullptr};
    };

    Node*       m_head{nullptr};
    Node*       m_tail{nullptr};
    std::size_t m_size{0U};

    void clear() noexcept;
};

/* ********************  Implementation  ******************** */

template <typename T>
List<T>::List(List&& other) noexcept
    : m_head(other.m_head),
      m_tail(other.m_tail),
      m_size(other.m_size)
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0U;
}

template <typename T>
auto List<T>::operator=(List&& other) noexcept -> List&
{
    if (this != &other)
    {
        clear();
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0U;
    }
    return *this;
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void List<T>::clear() noexcept
{
    Node* current = m_head;
    while (current != nullptr)
    {
        Node* const nextNode = current->next;
        delete current;
        current = nextNode;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0U;
}

template <typename T>
void List<T>::push(const T& value)
{
    Node* const newNode = new Node(value);
    if (m_tail == nullptr)
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        m_tail->next = newNode;
        newNode->prev = m_tail;
        m_tail       = newNode;
    }
    ++m_size;
}

template <typename T>
T List<T>::pop()
{
    if (m_tail == nullptr)
    {
        throw std::out_of_range("pop on empty list");
    }

    Node* const oldTail = m_tail;
    T     value   = std::move(oldTail->data);

    m_tail = oldTail->prev;
    if (m_tail != nullptr)
    {
        m_tail->next = nullptr;
    }
    else
    {
        m_head = nullptr;
    }

    delete oldTail;
    --m_size;
    return value;
}

template <typename T>
void List<T>::unshift(const T& value)
{
    Node* const newNode = new Node(value);
    if (m_head == nullptr)
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        newNode->next = m_head;
        m_head->prev  = newNode;
        m_head        = newNode;
    }
    ++m_size;
}

template <typename T>
T List<T>::shift()
{
    if (m_head == nullptr)
    {
        throw std::out_of_range("shift on empty list");
    }

    Node* const oldHead = m_head;
    T     value   = std::move(oldHead->data);

    m_head = oldHead->next;
    if (m_head != nullptr)
    {
        m_head->prev = nullptr;
    }
    else
    {
        m_tail = nullptr;
    }

    delete oldHead;
    --m_size;
    return value;
}

template <typename T>
std::size_t List<T>::count() const noexcept
{
    return m_size;
}

template <typename T>
bool List<T>::erase(const T& value)
{
    Node* current = m_head;
    while (current != nullptr)
    {
        if (current->data == value)
        {
            if (current->prev != nullptr)
            {
                current->prev->next = current->next;
            }
            else
            {
                m_head = current->next;
            }

            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }
            else
            {
                m_tail = current->prev;
            }

            delete current;
            --m_size;
            return true;
        }
        current = current->next;
    }
    return false;
}

} // namespace linked_list
