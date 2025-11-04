#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_is_open(false),
      m_balance(static_cast<std::int32_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_is_open)
    {
        throw std::runtime_error("account already open");
    }
    m_balance = static_cast<std::int32_t>(0);
    m_is_open = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(!m_is_open)
    {
        throw std::runtime_error("account not open");
    }
    m_is_open = false;
}

void Bankaccount::deposit(std::int32_t amount)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(!m_is_open)
    {
        throw std::runtime_error("account not open");
    }
    if(amount < static_cast<std::int32_t>(0))
    {
        throw std::invalid_argument("negative deposit");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int32_t amount)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(!m_is_open)
    {
        throw std::runtime_error("account not open");
    }
    if(amount < static_cast<std::int32_t>(0))
    {
        throw std::invalid_argument("negative withdrawal");
    }
    if(m_balance < amount)
    {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

std::int32_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(!m_is_open)
    {
        throw std::runtime_error("account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
