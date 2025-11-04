#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_balance(0),
      m_is_open(false),
      m_mutex() {}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open)
    {
        throw std::runtime_error("Account already open");
    }
    m_is_open = true;
    m_balance = 0;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account already closed");
    }
    m_is_open = false;
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account is not open");
    }
    if (amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("Deposit amount must be non-negative");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account is not open");
    }
    if (amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }
    if (m_balance < amount)
    {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account is not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
