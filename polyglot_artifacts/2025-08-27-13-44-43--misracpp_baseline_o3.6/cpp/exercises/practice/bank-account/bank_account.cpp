#include "bank_account.h"

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_);
    if (open_) {
        throw std::runtime_error("Account already open");
    }
    open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("Account already closed");
    }
    open_ = false;
}

void Bankaccount::deposit(int amount) {
    if (amount < 0) {
        throw std::runtime_error("Negative deposit");
    }
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("Account closed");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount < 0) {
        throw std::runtime_error("Negative withdraw");
    }
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("Account closed");
    }
    if (balance_ < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("Account closed");
    }
    return balance_;
}

}  // namespace Bankaccount
