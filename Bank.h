#ifndef BANK_H
#define BANK_H
#include "Account.h" 
#include <bits/stdc++.h>
using namespace std;

class Bank
{
private:
    vector<Account *> accounts;
    int nextAccountnumber = 1001;

public:
    void create_saving_account(string name, double balance, double rate);
    void create_current_account(string name, double balance, double overdraft_limit);
    Account *find_acc(int account_no);
    void deposit_to_account(int account_no, int amount);
    void withdraw_from_account(int account_no, int amount);
    void transaction_between_accounts(int from_account_no, int to_account_no, int amount);
    void close_account(int account_no);
    void Edit_Account_Details(int account_no, string new_name);
    void Auto_generate_saving_interest();
    void Minimum_balace_Warning();
    void displayAllAccounts();
};

#endif