#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("account already open");
    } else {
        is_open_ = true;
        balance_ = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    } else {
        is_open_ = false;
        balance_ = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::deposit(std::int64_t amount) {
    if ((amount <= static_cast<std::int64_t>(0))) {
        throw std::runtime_error("deposit amount must be positive");
    } else {
        // proceed
    }

    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    } else {
        balance_ = (balance_ + amount);
    }
}

void Bankaccount::withdraw(std::int64_t amount) {
    if ((amount <= static_cast<std::int64_t>(0))) {
        throw std::runtime_error("withdrawal amount must be positive");
    } else {
        // proceed
    }

    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    } else {
        if ((amount > balance_)) {
            throw std::runtime_error("insufficient funds");
        } else {
            balance_ = (balance_ - amount);
        }
    }
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("account not open");
    } else {
        return balance_;
    }
}

}  // namespace Bankaccount
