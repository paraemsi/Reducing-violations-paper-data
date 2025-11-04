#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount()
    : balance_(0), is_open_(false)
{
}

Bankaccount::~Bankaccount()
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("Account is already open");
    }
    is_open_ = true;
    balance_ = static_cast<money_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is not open");
    }
    is_open_ = false;
}

void Bankaccount::deposit(money_t amount)
{
    if (amount < static_cast<money_t>(0)) {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    balance_ = (balance_ + amount);
}

void Bankaccount::withdraw(money_t amount)
{
    if (amount < static_cast<money_t>(0)) {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
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
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount
