#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open()
{
    std::scoped_lock<std::mutex> lock(m_mutex_);
    if (!m_is_open_)
    {
        m_is_open_ = true;
        m_balance_ = static_cast<amount_t>(0);
    }
    else
    {
        throw std::runtime_error("Account already open");
    }
}

void Bankaccount::close()
{
    std::scoped_lock<std::mutex> lock(m_mutex_);
    if (m_is_open_)
    {
        m_is_open_ = false;
    }
    else
    {
        throw std::runtime_error("Account not open");
    }
}

void Bankaccount::deposit(amount_t amount)
{
    std::scoped_lock<std::mutex> lock(m_mutex_);
    if (!m_is_open_)
    {
        throw std::runtime_error("Account not open");
    }
    if (amount < static_cast<amount_t>(0))
    {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    m_balance_ += amount;
}

void Bankaccount::withdraw(amount_t amount)
{
    std::scoped_lock<std::mutex> lock(m_mutex_);
    if (!m_is_open_)
    {
        throw std::runtime_error("Account not open");
    }
    if (amount < static_cast<amount_t>(0))
    {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    if (m_balance_ < amount)
    {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance_ -= amount;
}

amount_t Bankaccount::balance() const
{
    std::scoped_lock<std::mutex> lock(m_mutex_);
    if (!m_is_open_)
    {
        throw std::runtime_error("Account not open");
    }
    return m_balance_;
}

}  // namespace Bankaccount
