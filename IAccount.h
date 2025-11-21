#ifndef IACCOUNT_H
#define IACCOUNT_H
#include <string>

class IAccount
{

public:
    virtual ~IAccount() = default;

    virtual int get_Account_No() const=0;
    virtual std::string get_account_holder_name()const=0;
    virtual double get_balance()const=0;
    
    virtual bool deposit(double amount);
    virtual bool withdraw(double amount);
    
    virtual void print_transaction_history()const=0;
    virtual void exportHistory(const std::string& filename) const=0;
};

#endif