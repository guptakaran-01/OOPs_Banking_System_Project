#include "Bank.h"
#include <bits/stdc++.h>
using namespace std;

// Account Creation
void Bank::create_saving_account(string name, double balance, double rate)
{
    Account *acc = new Saving_Account(nextAccountnumber++, name, balance, rate);
    accounts.push_back(acc);
    cout << "Saving Account created " << endl;
}
void Bank::create_current_account(string name, double balance, double overdraft_limit)
{
    Account *acc = new Current_Account(nextAccountnumber++, name, balance, overdraft_limit);
    accounts.push_back(acc);
    cout << "Current Account created " << endl;
}

// finding Account
Account *Bank::find_acc(int account_no)
{
    for (auto acc : accounts)
    {
        if (acc->get_Account_No() == account_no)
        {
            return acc;
        }
    }

    return NULL; // If no account found
}

void Bank::deposit_to_account(int account_no, int amount)
{
    Account *acc = find_acc(account_no);
    if (acc != NULL)
    {
        if (acc->deposit(amount))
        {
            cout << "Your Amount was deposited. Current balance: " << acc->get_balance() << endl;
        }
        else
        {
            cout << "Amount failed to deposit " << endl;
        }
    }
    else
    {
        cout << "Account not found" << endl;
    }
}
void Bank::withdraw_from_account(int account_no, int amount)
{
    Account *acc = find_acc(account_no);
    if (acc != NULL)
    {
        if (acc->withdraw(amount))
        {
            cout << "Your amount was debited. Current balance:  " << acc->get_balance() << endl;
        }
        else
        {
            cout << "transaction failed " << endl;
        }
    }
    else
    {
        cout << "Account not found" << endl;
    }
}

void Bank::transaction_between_accounts(int from_account_no, int to_account_no, int amount)
{
    Account *acc1 = find_acc(from_account_no);
    Account *acc2 = find_acc(to_account_no);
    if (acc1 != NULL && acc2 != NULL)
    {
        if (acc1->withdraw(amount))
        {
            if (acc2->deposit(amount))
            {
                cout << "Transaction completed succesfull" << endl;
            }
            else
            {
                acc1->deposit(amount);
                cout << "Transacrion failed  as deposit failed so withdrwal rolled back " << endl;
            }
        }
    }
    else
    {
        cout << "Transaction failed" << endl;
    }
}

void Bank::close_account(int account_no)
{
    for (auto acc = accounts.begin(); acc != accounts.end(); acc++)
    {
        if ((*acc)->get_Account_No() == account_no)
        {
            delete *acc;
            accounts.erase(acc);
            cout << "Account deleted successfully" << endl;
            return;
        }
    }
    cout << "No Account found" << endl;
}

void Bank::Edit_Account_Details(int account_no, string new_name)
{
    Account *acc = find_acc(account_no);
    if (acc != NULL)
    {
        acc->setname(new_name);
        cout << "Edited successfully" << endl;
    }
    else
    {
        cout << "Edit request failed" << endl;
    }
}

void Bank::Auto_generate_saving_interest()
{
    for (auto acc : accounts)
    {
        Saving_Account *sa = dynamic_cast<Saving_Account *>(acc);
        if (sa != NULL)
        {
            if (sa->addInterest())
            {
                cout << "Interest added succesfully" << endl;
            }
            else
            {
                cout << "Failed to add interest" << endl;
            }
        }
    }
}

void Bank::Minimum_balace_Warning()
{
    for (auto acc : accounts)
    {
        if (acc->get_balance() < 500)
        {
            cout << "Account balance low in accounts : " << acc->get_Account_No() << endl;
        }
    }
}

void Bank::displayAllAccounts()
{
    for (auto acc : accounts)
    {
        cout << "--------------------" << endl;
        acc->displayBalance();
        cout << "--------------------" << endl;
    }
}