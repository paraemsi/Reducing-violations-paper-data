#include "bank_account.h"

#include <stdexcept>
#include <limits>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept : m_mutex(), m_open(false), m_balance(0U)
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> const lock(m_mutex);

    if(m_open)
    {
        throw std::runtime_error("Account already open");
    }
    m_balance = static_cast<std::uint64_t>(0U);
    m_open = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> const lock(m_mutex);

    if(!m_open)
    {
        throw std::runtime_error("Account already closed");
    }
    m_open = false;
    m_balance = static_cast<std::uint64_t>(0U);
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> const lock(m_mutex);

    if(!m_open)
    {
        throw std::runtime_error("Account is not open");
    }

    if(amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("Negative deposit not allowed");
    }

    std::uint64_t const uamount = static_cast<std::uint64_t>(amount);

    if(m_balance > (std::numeric_limits<std::uint64_t>::max() - uamount))
    {
        throw std::runtime_error("Balance overflow");
    }

    m_balance += uamount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> const lock(m_mutex);

    if(!m_open)
    {
        throw std::runtime_error("Account is not open");
    }

    if(amount < static_cast<std::int64_t>(0))
    {
        throw std::runtime_error("Negative withdraw not allowed");
    }

    std::uint64_t const uamount = static_cast<std::uint64_t>(amount);

    if(uamount > m_balance)
    {
        throw std::runtime_error("Insufficient funds");
    }

    m_balance -= uamount;
}

std::uint64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> const lock(m_mutex);

    if(!m_open)
    {
        throw std::runtime_error("Account is not open");
    }

    return m_balance;
}

}  // namespace Bankaccount
