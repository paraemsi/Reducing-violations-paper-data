#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : balance_(static_cast<int_type>(0)), is_open_(false)
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_);
    if (is_open_ != false)
    {
        throw std::runtime_error("Account already open");
    }
    is_open_ = true;
    balance_ = static_cast<int_type>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_);
    if (is_open_ == false)
    {
        throw std::runtime_error("Account already closed");
    }
    is_open_ = false;
    balance_ = static_cast<int_type>(0);
}

void Bankaccount::deposit(int_type amount)
{
    std::lock_guard<std::mutex> lock(m_);
    if (is_open_ == false)
    {
        throw std::runtime_error("Account not open");
    }
    if (amount < static_cast<int_type>(0))
    {
        throw std::runtime_error("Deposit amount must be non-negative");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int_type amount)
{
    std::lock_guard<std::mutex> lock(m_);
    if (is_open_ == false)
    {
        throw std::runtime_error("Account not open");
    }
    if (amount < static_cast<int_type>(0))
    {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }
    if (balance_ < amount)
    {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

Bankaccount::int_type Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_);
    if (is_open_ == false)
    {
        throw std::runtime_error("Account not open");
    }
    return balance_;
}

}  // namespace Bankaccount
