#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <memory>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount() = default;
    Bankaccount(const Bankaccount&) = default;
    Bankaccount& operator=(const Bankaccount&) = default;
    Bankaccount(Bankaccount&&) noexcept = default;
    Bankaccount& operator=(Bankaccount&&) noexcept = default;

    void open();
    void close();
    void deposit(int amount);
    void withdraw(int amount);
    int balance() const;

private:
    struct State {
        bool opened{false};
        int balance{0};
        mutable std::mutex m;
    };
    std::shared_ptr<State> state_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
