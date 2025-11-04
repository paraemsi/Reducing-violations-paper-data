#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open)
    {
        throw std::runtime_error("Account already open");
    }
    m_open = true;
    m_balance = static_cast<std::int64_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("Account already closed");
    }
    m_open = false;
}

void Bankaccount::deposit(const std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("Negative deposit");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("Account closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(const std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("Negative withdraw");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("Account closed");
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
    if (!m_open)
    {
        throw std::runtime_error("Account closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
