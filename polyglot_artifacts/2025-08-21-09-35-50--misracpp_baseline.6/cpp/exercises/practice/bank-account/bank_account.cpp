#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount() : is_open_(false), balance_(0) {}

Bankaccount::~Bankaccount() {}

#include <stdexcept>

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (is_open_) {
        throw std::runtime_error("Account already open");
    }
    is_open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account not open");
    }
    is_open_ = false;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!is_open_) {
        throw std::runtime_error("Account is closed");
    }
    return balance_;
}

}  // namespace Bankaccount
