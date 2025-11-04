#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount()
    : balance_(0), open_(false)
{
}

Bankaccount::~Bankaccount()
{
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

bool Bankaccount::is_open() const
{
    std::lock_guard<std::mutex> lock(mtx_);
    return open_;
}

bool Bankaccount::deposit(money_t amount)
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!open_ || (amount < static_cast<money_t>(0))) {
        return false;
    }
    balance_ = (balance_ + amount);
    return true;
}

bool Bankaccount::withdraw(money_t amount)
{
    std::lock_guard<std::mutex> lock(mtx_);
    if ((!open_) || (amount < static_cast<money_t>(0)) || (amount > balance_)) {
        return false;
    }
    balance_ = (balance_ - amount);
    return true;
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
