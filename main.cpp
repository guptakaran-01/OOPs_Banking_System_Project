#include "Bank.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    Bank bank;

    // Example usage
    bank.create_saving_account("Hari", 8000, 5);
    bank.create_current_account("Rohan", 3000, 3000);

    bank.deposit_to_account(1001, 500);
    bank.withdraw_from_account(1002, 1000);

    bank.displayAllAccounts();
   

    bank.create_saving_account("Hari", 13000, 5);
    bank.create_current_account("Hari", 10000, 500);

    bank.auto_generate_report();


    return 0;
}