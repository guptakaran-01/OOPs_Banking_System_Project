#ifndef Account_H
#define Account_H

#include <bits/stdc++.h>
using namespace std;

class Account
{
private:
    int Account_no;
    string account_holder_name;
    double balance;

public:
    Account(int Account_no, string name, double balance);
    void setname(string name);
    int get_Account_No();
    string get_account_holder_name();
    double get_balance();
    bool deposit(double amount);
    virtual bool withdraw(double amount);
    void change_balance(double amount);
    void displayBalance();
};

class Saving_Account : public Account
{
private:
    double interest_rate;

public:
    Saving_Account(int Account_no, string name, double balance, double rate);
    bool addInterest();
};

class Current_Account : public Account
{
private:
    double over_draft_limit;

public:
    Current_Account(int Account_no, string name, double balance, double overdraft_limit);
    bool withdraw(double amount) override;
};

#endif