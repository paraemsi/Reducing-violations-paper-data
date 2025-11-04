#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(), m_is_open(false), m_balance(balance_t{0})
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_is_open)
    {
        throw std::runtime_error("Account already open");
    }
    m_is_open = true;
    m_balance = balance_t{0};
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account already closed");
    }
    m_is_open = false;
}

void Bankaccount::deposit(balance_t amount)
{
    if (amount <= balance_t{0})
    {
        throw std::invalid_argument("Deposit amount must be positive");
    }

    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account is closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(balance_t amount)
{
    if (amount <= balance_t{0})
    {
        throw std::invalid_argument("Withdraw amount must be positive");
    }

    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account is closed");
    }
    if (amount > m_balance)
    {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

Bankaccount::balance_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount

