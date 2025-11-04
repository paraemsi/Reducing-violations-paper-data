#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept :
    m_mutex(),
    m_open(false),
    m_balance(static_cast<money_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_open)
    {
        throw std::runtime_error("Account is already open.");
    }

    m_open = true;
    m_balance = static_cast<money_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open)
    {
        throw std::runtime_error("Account is already closed.");
    }

    m_open = false;
}

void Bankaccount::deposit(const money_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open)
    {
        throw std::runtime_error("Account is not open.");
    }

    if (amount < static_cast<money_t>(0))
    {
        throw std::runtime_error("Cannot deposit a negative amount.");
    }

    m_balance += amount;
}

void Bankaccount::withdraw(const money_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open)
    {
        throw std::runtime_error("Account is not open.");
    }

    if (amount < static_cast<money_t>(0))
    {
        throw std::runtime_error("Cannot withdraw a negative amount.");
    }

    if (m_balance < amount)
    {
        throw std::runtime_error("Insufficient funds.");
    }

    m_balance -= amount;
}

money_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open)
    {
        throw std::runtime_error("Account is not open.");
    }

    return m_balance;
}

}  // namespace Bankaccount
