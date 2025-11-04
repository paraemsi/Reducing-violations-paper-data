#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_open(false),
      m_balance(static_cast<amount_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        m_balance = static_cast<amount_t>(0);
        m_open = true;
    }
    else
    {
        throw std::runtime_error("account already open");
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open)
    {
        m_open = false;
        m_balance = static_cast<amount_t>(0);
    }
    else
    {
        throw std::runtime_error("account is not open");
    }
}

void Bankaccount::deposit(amount_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    if (amount < static_cast<amount_t>(0))
    {
        throw std::runtime_error("amount must be non-negative");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(amount_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    if (amount < static_cast<amount_t>(0))
    {
        throw std::runtime_error("amount must be non-negative");
    }
    if (m_balance < amount)
    {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

amount_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open)
    {
        throw std::runtime_error("account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
