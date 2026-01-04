#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <conio.h>
#include <string>
#include <string.h>
#include <limits>
using namespace std;
int pass;
int pass_count = 0;
int pass_deposit = 0;
int pass_withdraw = 0;
string accn;

struct info
{
    string account_number;
    int balance;
    int withdraw;
    int pin;
    string status;
};

int verification();
void attempts();
void interface();
void Deposit();
void withdraw();
void view_balance();
void Pin_change();
int admin_verification();
void administrator_add();
void administrator_delete();
void show_all_accounts();

int verification()
{
    int i = 0;
    int pin;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To clear buffer
    string account_number;
    cout << "Verify Yourself First\n";
    cout << "Enter your account number: ";
    getline(cin, account_number);
    cout << "Enter your pin to verify: ";
    cin >> pin;
    ifstream rfile("account_data.txt");
    string line;
    int is_allow = 0;

    while (getline(rfile, line))
    {
        istringstream veri(line);
        info verify;
        veri >> verify.account_number;
        veri >> verify.pin;
        veri >> verify.balance;
        veri >> verify.status;

        if (pin == verify.pin && verify.account_number == account_number)
        {
            is_allow = 1;
            pass = pin;
            accn = account_number;
        }
    }
    rfile.close();

    if (is_allow)
    {
        cout << "Access granted\n";
        i = 0;
        return 1;
    }

    else
    {
        int should_go = 0;
        string re_account_number;
        int re_Pin;
        ifstream Rz("account_data.txt");
        fstream update_accounts("account_data_temp.txt", ios::app);

        if (!Rz.is_open())
        {
            cout << "Error opening file";
        }

        for (int j = 0; j < 3; j++)
        {
            pass_count++;
            cout << "Access permitted\n";
            cout << "Please enter correct PIN\n";
            cout << "Enter your account_number again: ";
            cin >> re_account_number;
            cout << "Enter Your PIN: ";
            cin >> re_Pin;
            int is_block;
            string b;
            ifstream readfile("account_data.txt");

            if (!readfile.is_open())
            {
                cout << "Error opening file";
            }

            while (getline(readfile, b))
            {
                istringstream dobara(b);
                info again_verify;
                dobara >> again_verify.account_number;
                dobara >> again_verify.pin;
                dobara >> again_verify.balance;
                dobara >> again_verify.status;

                if (re_Pin == again_verify.pin && again_verify.account_number == re_account_number)
                {
                    is_allow = 1;
                    pass = re_Pin;
                    accn = re_account_number;
                    break;
                }
            }

            if (is_allow)
            {
                cout << "Pin verification Successful\n";
                cout << "You Login successful in " << pass_count + 1 << " attempts";
                return 1;
                break;
            }

            readfile.close();

            if (j == 2)
            {
                cout << "You have tried for Four times\n";
                cout << "For this your account has been blocked\n";
                string block_account;

                while (getline(Rz, block_account))
                {
                    istringstream bl(block_account);
                    info block;
                    bl >> block.account_number;
                    bl >> block.pin;
                    bl >> block.balance;
                    bl >> block.status;
                    if (re_account_number == block.account_number)
                    {
                        fstream bfile("Blocked_accounts.txt", ios::app);
                        bfile << block.account_number << " " << block.pin << " ";
                        bfile << block.balance << " " << block.status << endl;
                        should_go = 1;
                    }

                    else
                    {
                        update_accounts << block.account_number << " " << block.pin << " ";
                        update_accounts << block.balance << " " << block.status << endl;
                    }
                }
            }
        }
        Rz.close();
        update_accounts.close();

        if (should_go)
        {
            cout << "Bsdk Account Blocked!\n";
            remove("account_data.txt");
            rename("account_data_temp.txt", "account_data.txt");
            return 0;
        }

        else
        {
            remove("account_data_temp.txt");
            cout << "Your account doesn't exist!\n";
            return 0;
        }
    }
}

int main()
{
    int pick;
    cout << "ATM and Account management system............\n";
    cout << "1. User\n";
    cout << "2. Administrator\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> pick;

    int i = 1;
    switch (pick)
    {
    case 1:
    {
        system("cls");
        int value;
        value = verification();
        do
        {
            if (value)
            {
                system("cls");
                int choice;
                interface();
                cin >> choice;
                switch (choice)
                {
                case 1:
                    system("cls");
                    withdraw();
                    cout << "Enter any key and enter to continue....... ";
                    getch();
                    break;

                case 2:
                    system("cls");
                    cout << "Deposit Money Section\n";
                    Deposit();
                    cout << "Enter any key and enter to continue....... ";
                    getch();
                    break;

                case 3:
                    system("cls");
                    view_balance();
                    cout << "Enter any key and enter to continue....... ";
                    getch();
                    break;

                case 4:
                    system("cls");
                    Pin_change();
                    cout << "Enter any key and enter to continue....... ";
                    getch();
                    break;

                case 5:
                    attempts();
                    i = 0;
                    cout << "Exiting.............";
                    getch();
                    break;
                default:
                    break;
                }
            }

            else
            {
                cout << "Invalid verification failed\n";
                i = 0;
                cout << "Exiting.............";
                getch();
            }

        } while (i);

        break;
    }

    case 2:
    {

        string verify;
        string code, username, input_username;
        int choice;
        username= "haroon12";
        code = "1q2w3e4r";
        cout << "Verification...................\n";
        cout<<"Enter your username: ";
        cin>>input_username;
        cout << "Enter 8 digit code to continue: ";
        cin >> verify;
        if (verify == code && username == input_username)
        {

            do
            {
                system("cls");
                cout << "\nWelcome to ATM system as Admin\n";
                cout << "01. Add account\n";
                cout << "02. Delete account\n";
                cout << "03. View all accounts details\n";
                cout << "04. Exit\n";
                cout << "Which function would you like to perform: ";
                cin >> choice;
                system("cls");
                if (verify == code)
                {
                    switch (choice)
                    {
                    case 01:
                        system("cls");
                        cout<<"Adding Account Section";
                        administrator_add();
                        cout << "Enter any key and enter to continue....... ";
                        getch();
                        break;

                    case 02:
                        system("cls");
                        cout<<"Deleting Account Section";
                        administrator_delete();
                        cout << "Enter any key and enter to continue....... ";
                        getch();
                        break;
                    case 03:
                        system("cls");
                        cout<<"Showing Account Section";
                        show_all_accounts();
                        cout << "Enter any key and enter to continue.......\n ";
                        getch();
                        break;

                    case 04:
                        break;

                    default:
                        break;
                    }
                }

            } while (i);
        }

        else
        {
            cout<<"Invalid Password";
        }
        

        break;
    }
    case 3:
    {
        break;
    }

    default:
    {
        break;
    }
    }
}

void interface()
{
    cout << "***** Welcome to Menu *****\n";
    cout << "1. Withdraw money\n";
    cout << "2. Deposit Money\n";
    cout << "3. View Balance\n";
    cout << "4. Change Pin\n";
    cout << "5. exit\n";
    cout << "Enter your choice: ";
}

void Deposit()
{
    string line;
    ifstream read("account_data.txt");
    fstream update_balance("account_data_temp.txt", ios::app);
    if (!read.is_open())
    {
        cout << "Error opening file\n";
    }

    if (!update_balance)
    {
        cout << "Error opening file\n";
    }

    int access = 0;
    int deposit;
    cout << "Enter money you want to deposit: ";
    cin >> deposit;
    while (getline(read, line))
    {
        istringstream dd(line);
        info deposit_money;

        dd >> deposit_money.account_number;
        dd >> deposit_money.pin;
        dd >> deposit_money.balance;
        dd >> deposit_money.status;

        if (::pass == deposit_money.pin)
        {
            int final_balance = deposit_money.balance + deposit;
            update_balance << deposit_money.account_number << " " << deposit_money.pin << " ";
            update_balance << final_balance << " " << deposit_money.status << endl;
            pass_deposit += deposit;
            access = 1;
        }

        else
        {
            update_balance << deposit_money.account_number << " " << deposit_money.pin << " ";
            update_balance << deposit_money.balance << " " << deposit_money.status << endl;
        }
    }
    read.close();
    update_balance.close();

    if (access)
    {
        remove("account_data.txt");
        rename("account_data_temp.txt", "account_data.txt");
        cout << "Your Balance Has Been Updated\n";
    }
    else
    {
        remove("account_data_temp.txt");
        cout << "Balance couldn't be updated\n";
    }
}

void withdraw()
{
    int i = 1;
    do
    {
        string line;
        ifstream read("account_data.txt");
        fstream update_balance("account_data_temp.txt", ios::app);
        if (!read.is_open())
        {
            cout << "Error opening file\n";
        }
        // int pin;
        // cout<<"Enter account Pin to Withdraw money: ";
        // cin>>pin;
        int access = 0;

        int withdraw;
        cout << "\n--------------WithDraw Rules-------------------\n";
        cout << "You can withdraw 20000 Rs at one time\n";
        cout << "Entered money should be multiple of 500\n\n";
        cout << "Enter money you want to deposit: ";
        cin >> withdraw;
        if (withdraw < 20000 && withdraw % 500 == 0 && withdraw >= 500)
        {
            while (getline(read, line))
            {
                istringstream dd(line);
                info withdraw_money;

                dd >> withdraw_money.account_number;
                dd >> withdraw_money.pin;
                dd >> withdraw_money.balance;
                dd >> withdraw_money.status;

                if (::pass == withdraw_money.pin)
                {
                    if (withdraw_money.balance != 0)
                    {
                        int final_balance = withdraw_money.balance - withdraw;
                        update_balance << withdraw_money.account_number << " " << withdraw_money.pin << " ";
                        update_balance << final_balance << " " << withdraw_money.status << endl;
                        pass_withdraw += withdraw;
                        access = 1;
                    }
                    else
                    {
                        cout << "Insufficient balance...\n";
                        access = 0;
                    }
                }
                else
                {
                    update_balance << withdraw_money.account_number << " " << withdraw_money.pin << " ";
                    update_balance << withdraw_money.balance << " " << withdraw_money.status << endl;
                }
            }
            read.close();
            update_balance.close();

            if (access)
            {
                remove("account_data.txt");
                rename("account_data_temp.txt", "account_data.txt");
                cout << "Your balance has been updated successfuly\n";
                i = 0;
            }
            else
            {
                remove("account_data_temp.txt");
                cout << "Withdraw Failed\n";
                i = 0;
            }
        }

        else
        {
            cout << "Invalid Input......";
        }

    } while (i);
}

void view_balance()
{
    string line;
    ifstream read("account_data.txt");
    if (!read.is_open())
    {
        cout << "Error opening file\n";
    }
    cout << "Your Details Section\n";

    while (getline(read, line))
    {
        istringstream dd(line);
        info withdraw_money;

        dd >> withdraw_money.account_number;
        dd >> withdraw_money.pin;
        dd >> withdraw_money.balance;
        dd >> withdraw_money.status;

        if (::pass == withdraw_money.pin)
        {
            cout << "Account number: " << withdraw_money.account_number << "\nPin number: " << withdraw_money.pin << " ";
            cout << "Current Balance: " << withdraw_money.balance << "\nAccount Status: " << withdraw_money.status << endl;
            break;
        }
    }
    read.close();
}

void Pin_change()
{

    string line;
    ifstream read("account_data.txt");
    fstream update_balance("account_data_temp.txt", ios::app);
    if (!read.is_open())
    {
        cout << "Error opening file\n";
    }
    // int pin;
    // cout<<"Enter account Pin to Withdraw money: ";
    // cin>>pin;
    int access = 0;
    char select;
    cout << "Pin Change Section\n";
    cout << "Do you want to change your pin(y/n): ";
    cin >> select;
    int new_pin;
    if (select == 'y' || select == 'Y')
    {
        cout << "Enter New Pin: ";
        cin >> new_pin;
        while (getline(read, line))
        {
            istringstream dd(line);
            info change_pin;

            dd >> change_pin.account_number;
            dd >> change_pin.pin;
            dd >> change_pin.balance;
            dd >> change_pin.status;

            if (::pass == change_pin.pin)
            {
                update_balance << change_pin.account_number << " " << new_pin << " ";
                update_balance << change_pin.balance << " " << change_pin.status << endl;
                access = 1;
            }
            else
            {
                update_balance << change_pin.account_number << " " << change_pin.pin << " ";
                update_balance << change_pin.balance << " " << change_pin.status << endl;
            }
        }
        read.close();
        update_balance.close();

        const char *file_name = "account_data.txt";
        if (access)
        {
            remove("account_data.txt");
            rename("account_data_temp.txt", "account_data.txt");
            cout << "Your PIN has been changed successfuly\n";
        }
        else
        {
            remove("account_data_temp.txt");
            cout << "PIN changing failed\n";
        }
    }

    else
    {
        cout << "Closing...........\n";
    }
}

void administrator_add()
{
    // Administrator can perform two actions delete account add account
    fstream addaccount("account_data.txt", ios::app);
    if (!addaccount.is_open())
    {
        cout << "Error opening file\n";
    }

    info accout_addition;
    cout << "Enter account number: ";
    cin >> accout_addition.account_number;
    cout << "Set a Pin: ";
    cin >> accout_addition.pin;
    accout_addition.balance = 0;
    cout << "Set status of account: ";
    cin >> accout_addition.status;
    addaccount << "\n"
               << accout_addition.account_number << " " << accout_addition.pin << " " << accout_addition.balance << " " << accout_addition.status;
}

void administrator_delete()
{
    string line;
    ifstream read("account_data.txt");
    fstream delete_acc("account_data_temp.txt", ios::app);

    if (!read.is_open())
    {
        cout << "Error opening file\n";
    }

    int access = 0;

    string account_number;
    cout << "Enter account number to delete: ";
    cin >> account_number;

    while (getline(read, line))
    {
        istringstream dd(line);
        info del_account;

        dd >> del_account.account_number;
        dd >> del_account.pin;
        dd >> del_account.balance;
        dd >> del_account.status;

        if (account_number == del_account.account_number)
        {
            access = 1;
            continue;
        }

        else
        {
            delete_acc << del_account.account_number << " " << del_account.pin << " ";
            delete_acc << del_account.balance << " " << del_account.status << endl;
        }
    }
    read.close();
    delete_acc.close();

    if (access)
    {
        remove("account_data.txt");
        rename("account_data_temp.txt", "account_data.txt");
        cout << "Account Deleted Successfuly\n";
    }

    else
    {
        remove("account_data_temp.txt");
        cout << "Account couldn't be deleted\n";
    }
}

void show_all_accounts()
{
    string line;
    ifstream read("account_data.txt");
    if (!read.is_open())
    {
        cout << "Error opening file\n";
    }
    info show_all_data;

    cout << "Accountnumber AccountPin Accountbalance Status\n";
    while (getline(read, line))
    {
        cout << line;
        cout << "\n";
    }

    read.close();
}

void attempts()
{
    fstream tries("History.txt", ios::app);
    tries << "\n"<< ::accn << "       " << pass_count + 1 << "       " << pass_deposit << "       " << pass_withdraw << endl;
    tries.close();
}
