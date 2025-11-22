#ifndef Account_H
#define Account_H

#include "Transaction.h"
#include "IAccount.h"

#include <string>
#include <vector>

class Account : public IAccount
{
private:
    int Account_no;
    std::string account_holder_name;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account(int Account_no, const std::string &name, double balance);
    virtual ~Account() = default;
    void setname(const std::string &name);

    int get_Account_No() const override;
    std::string get_account_holder_name() const override;
    double get_balance() const override;

    bool deposit(double amount) override;
    virtual bool withdraw(double amount) override = 0;

    void displayBalance() const;

    void print_transaction_history() const override;
    void exportHistory(const std::string &filename) const override;

protected:
    void change_balance(double amount);
    void record_transaction(const std::string &type, double amount);
};

class Saving_Account : public Account
{
private:
    double interest_rate;

public:
    Saving_Account(int Account_no, const std::string &name, double balance, double rate);
    bool addInterest();
};

class Current_Account : public Account
{
private:
    double over_draft_limit;

public:
    Current_Account(int Account_no, const std::string &name, double balance, double overdraft_limit);
    bool withdraw(double amount) override;
};

#endif