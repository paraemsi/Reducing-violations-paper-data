#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_is_open(false),
      m_balance(static_cast<std::int64_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open)
    {
        throw std::runtime_error("account already open");
    }
    m_is_open = true;
    m_balance = static_cast<std::int64_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("account already closed");
    }
    m_is_open = false;
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("account closed");
    }

    /* If the operation would overdraw the account, reject it */
    if ((amount < static_cast<std::int64_t>(0)) &&
        (m_balance < (-amount)))
    {
        throw std::runtime_error("insufficient funds");
    }

    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount <= static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("withdraw must be positive");
    }

    /* Re-use deposit logic by passing a negative amount */
    deposit(-amount);
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open)
    {
        throw std::runtime_error("account closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
