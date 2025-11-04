#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_);
    if (is_open_) {
        throw std::runtime_error("account already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_);
    if (!is_open_) {
        throw std::runtime_error("account already closed");
    }
    is_open_ = false;
    balance_ = 0;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_);
    if (!is_open_) {
        throw std::runtime_error("account closed");
    }
    return balance_;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(m_);
    if (!is_open_) {
        throw std::runtime_error("account closed");
    }
    // Treat negative amounts as a withdrawal while guarding against overdraft.
    if (amount < 0 && balance_ + amount < 0) {
        throw std::runtime_error("overdraft");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(m_);
    if (!is_open_) {
        throw std::runtime_error("account closed");
    }
    if (amount < 0) {
        throw std::invalid_argument("negative withdraw");
    }
    if (balance_ - amount < 0) {
        throw std::runtime_error("overdraft");
    }
    balance_ -= amount;
}

}  // namespace Bankaccount
