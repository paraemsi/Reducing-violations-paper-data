#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : state_(std::make_shared<State>()) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(state_->m);
    if (state_->opened) {
        throw std::runtime_error("account already open");
    }
    state_->opened = true;
    state_->balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(state_->m);
    if (!state_->opened) {
        throw std::runtime_error("account not open");
    }
    state_->opened = false;
}

void Bankaccount::deposit(int amount) {
    if (amount < 0) {
        throw std::runtime_error("cannot deposit negative amount");
    }
    std::lock_guard<std::mutex> lock(state_->m);
    if (!state_->opened) {
        throw std::runtime_error("account not open");
    }
    state_->balance += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount < 0) {
        throw std::runtime_error("cannot withdraw negative amount");
    }
    std::lock_guard<std::mutex> lock(state_->m);
    if (!state_->opened) {
        throw std::runtime_error("account not open");
    }
    if (state_->balance < amount) {
        throw std::runtime_error("insufficient funds");
    }
    state_->balance -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(state_->m);
    if (!state_->opened) {
        throw std::runtime_error("account not open");
    }
    return state_->balance;
}

}  // namespace Bankaccount
