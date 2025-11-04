#include "bank_account.h"

namespace Bankaccount
{

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if(m_is_open)
    {
        throw std::runtime_error("account already open");
    }
    m_is_open = true;
    m_balance = static_cast<std::int64_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if(!m_is_open)
    {
        throw std::runtime_error("account already closed");
    }
    m_is_open = false;
}

void Bankaccount::deposit(const std::int64_t amount)
{
    if(amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("negative deposit");
    }

    std::lock_guard<std::mutex> lock {m_mutex};

    if(!m_is_open)
    {
        throw std::runtime_error("account closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(const std::int64_t amount)
{
    if(amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("negative withdrawal");
    }

    std::lock_guard<std::mutex> lock {m_mutex};

    if(!m_is_open)
    {
        throw std::runtime_error("account closed");
    }
    if(m_balance < amount)
    {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if(!m_is_open)
    {
        throw std::runtime_error("account closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
