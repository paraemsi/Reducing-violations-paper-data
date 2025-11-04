#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount()
    : open_(false), balance_(0)
{
}

Bankaccount::~Bankaccount()
{
    // No dynamic resources to release
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(mtx_);
    open_ = true;
    balance_ = static_cast<money_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(mtx_);
    open_ = false;
}

void Bankaccount::deposit(money_t amount)
{
    if (amount < static_cast<money_t>(0)) {
        throw std::invalid_argument("Deposit amount must be non-negative");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account is closed");
    }
    balance_ = (balance_ + amount);
}

void Bankaccount::withdraw(money_t amount)
{
    if (amount < static_cast<money_t>(0)) {
        throw std::invalid_argument("Withdraw amount must be non-negative");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account is closed");
    }
    if (balance_ < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ = (balance_ - amount);
}

money_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

} // namespace Bankaccount
