#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_open(false),
      m_balance(static_cast<std::int64_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open)
    {
        throw std::runtime_error("account already open");
    }
    m_open = true;
    m_balance = static_cast<std::int64_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    m_open = false;
}

void Bankaccount::deposit(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("cannot deposit negative amount");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("cannot withdraw negative amount");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    if (m_balance < amount)
    {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
