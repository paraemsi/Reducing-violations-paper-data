#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount()
    : is_open_(false), balance_(0)
{
}

Bankaccount::~Bankaccount()
{
    // No dynamic resources to release
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("Account already open");
    }
    is_open_ = true;
    balance_ = static_cast<money_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account already closed");
    }
    is_open_ = false;
}

void Bankaccount::deposit(money_t amount)
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < static_cast<money_t>(0)) {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    balance_ = (balance_ + amount);
}

void Bankaccount::withdraw(money_t amount)
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < static_cast<money_t>(0)) {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    if (balance_ < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ = (balance_ - amount);
}

money_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

} // namespace Bankaccount
