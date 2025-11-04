#include "bank_account.h"

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : is_open_(false),
      balance_(static_cast<std::int64_t>(0)) {}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (is_open_ == true) {
        throw std::runtime_error("account already open");
    } else {
        is_open_ = true;
        balance_ = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (is_open_ == false) {
        throw std::runtime_error("account already closed");
    } else {
        is_open_ = false;
    }
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (is_open_ == false) {
        throw std::runtime_error("account is closed");
    } else {
        return balance_;
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("deposit amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(mutex_);

    if (is_open_ == false) {
        throw std::runtime_error("account is closed");
    } else {
        balance_ += amount;
    }
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("withdraw amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(mutex_);

    if (is_open_ == false) {
        throw std::logic_error("account is closed");
    }

    if (balance_ < amount) {
        throw std::runtime_error("insufficient funds");
    } else {
        balance_ -= amount;
    }
}

}  // namespace Bankaccount
