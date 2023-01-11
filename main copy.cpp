#include <iostream>
using namespace std;
#include <fstream>
#include <string>
void clear()
{
    ofstream file("users.txt");
    file<<"";
}
string hashedPassword(string password){
    for(int i=0;i<password.length();i++){
        password[i]=password[i]^'!';
    }
    return password;

}
int findUsersNumber(string name, string* names){
    int counter=0;
    for(counter;name!=names[counter];counter++);
    return counter;

}
bool isPasswordValid(string password){
    bool lowerCase= false;
    bool upperCase= false;
    bool number= false;
    bool specialSymbol=false;
    if(password.length()<5){
        cout<<"Password must contain more than 5 symbols\n";
        return false;
    }
    for(int i=0;i<password.length();i++){
        char letter=password[i];
        if(letter>=65 and letter<=90){
            upperCase= true;
        } else if(letter>=97 and letter<=122){
            lowerCase= true;
        } else if(letter>=48 and letter<=57){
            number= true;
        } else if(letter==33 or letter==64 or letter==35 or letter==36 or letter==37 or letter==94 or letter==38 or letter==42){
            specialSymbol= true;
        }
    }
    if(upperCase and lowerCase and number and specialSymbol){
        return true;
    } else {
        cout<<"Invalid password\n";
        return false;
    }

}
bool canUserRegister(string name,string password, string* names,int userCount){
    bool doesItExist= false;
    for(int i=0;i<userCount;i++){
        if(name==names[i]){
            doesItExist= true;
        }
    }
    if(doesItExist){
        cout<<"Username already taken\n";
        return false;
    }
    if(isPasswordValid(password)){
        return true;
    } else {
        return false;
    }

}
bool canUserLogin(string name,string password, string* names,string* passwords,int userCount){
    bool doesItExist= false;
    string truePassword;
    for(int i=0;i<userCount;i++){
        if(name==names[i]){
            doesItExist= true;
            truePassword=passwords[i];
        }
    }
    if(doesItExist){
        if(hashedPassword(password)==truePassword){
            return true;
        } else {
            cout<<"Wrong password\n";
            return false;
        }
    } else {
        cout<<"Username doesn't exist\n";
        return false;
    }

}

int main() {
    string names[20];
    string passwords[20];
    double balance[1024];
    int usersCount=0;
    string currentName;
    string currentPassword;
    double currentBalance;
    fstream my_file;
    my_file.open("users.txt");
    if (!my_file) {
        cout << "File not open!";
    }
    else {
        cout << "File opened successfully!\n";
        while(true){
            if(my_file.eof()){
                break;
            }
            my_file>>names[usersCount];
            my_file>>passwords[usersCount];
            my_file>>balance[usersCount];
            usersCount++;
        }
        usersCount--;
        my_file.close();
        cout<<"Please choose an option!\n";
        cout<<"L-login\n"<<"R-register\n"<<"Q-quit\n";
        string command;
        cin>>command;
        while (command!="Q"){
            if(command=="L"){
                cout<<"Please enter a username and a password\n";
                cin>>currentName;
                cin>>currentPassword;
                if(canUserLogin(currentName,currentPassword,names,passwords,usersCount)){
                    cout<<"Welcome "<<currentName<<endl;
                    int userNumber= findUsersNumber(currentName,names);
                    cout<<"You have "<<balance[userNumber]<<" BGN. Please choose an option!\n";
                    cout<<"C-cancel account\n"<<"D-deposit\n"<<"L-logout\n"<<"T-transfer\n"<<"W-withdraw\n";
                    cin>>command;
                    while (command!="L"){
                        if(command=="D"){
                            cout<<"Please enter amount you want to deposit\n";
                            double money;
                            cin>>money;
                            while (money<=0){
                                cout<<"Please enter valid amount\n";
                                cin>>money;
                            }
                            balance[userNumber]=balance[userNumber]+money;
                            cout<<"Successfully deposited money\n";

                        } else if(command=="T") {
                            cout<<"Please enter amount you want to transfer and the name of the account\n";
                            double money;
                            int secondNameNumber;
                            string secondName;
                            bool doesItExist=false;
                            cin>>money;
                            while (money<=0){
                                cout<<"Please enter valid amount\n";
                                cin>>money;
                            }
                            cin>>secondName;
                            for(int i=0;i<usersCount;i++){
                                if(names[i]==secondName){
                                    doesItExist= true;
                                    break;
                                }
                            }
                            if(doesItExist){
                                secondNameNumber= findUsersNumber(secondName,names);
                                if(balance[userNumber]-money<-10000){
                                    cout<<"You don't have enough money\n";
                                } else {
                                    balance[userNumber]=balance[userNumber]-money;
                                    balance[secondNameNumber]=balance[secondNameNumber]+money;
                                    cout<<"Successfully transferred "<<money<<" BGN to "<<secondName<<endl;
                                }
                            } else {
                                cout<<"This account doesn't exist\n";
                            }

                        } else if(command=="W"){
                            cout<<"Please enter amount you want to withdraw\n";
                            double money;
                            cin>>money;
                            while (money<=0){
                                cout<<"Please enter valid amount\n";
                                cin>>money;
                            }
                            if(balance[userNumber]-money<-10000){
                                cout<<"You don't have enough money\n";
                            } else {
                                balance[userNumber]=balance[userNumber]-money;
                                cout<<"Successfully withdrawn "<<money<<" BGN\n";
                            }
                        } else if(command=="C"){
                            cout<<"Please enter password\n";
                            string tryPassword;
                            cin>>tryPassword;
                            if(hashedPassword(tryPassword)==passwords[userNumber]){
                                if(balance[userNumber]!=0){
                                    cout<<"Cannot cancel account, your balance is not 0 BGN\n";
                                } else{
                                    names[userNumber]="0";
                                    cout<<"Successfully canceled account\n";
                                    break;
                                }
                            } else{
                                cout<<"Invalid password\n";
                            }
                        }else {
                            cout<<"Please enter valid letter\n";
                        }
                        cout<<"You have "<<balance[userNumber]<<" BGN. Please choose an option!\n";
                        cout<<"C-cancel account\n"<<"D-deposit\n"<<"L-logout\n"<<"T-transfer\n"<<"W-withdraw\n";
                        cin>>command;
                    }


                }
            } else if(command=="R") {
                cout<<"Please choose a free username and a password\n";
                cin>>currentName;
                cin>>currentPassword;
                if(canUserRegister(currentName,currentPassword,names,usersCount)){
                    names[usersCount]=currentName;
                    passwords[usersCount]= hashedPassword(currentPassword);
                    balance[usersCount]=0;
                    usersCount++;
                    cout<<"Register successfully\n";
                    cout<<"Welcome "<<currentName<<endl;
                    cout<<"You have 0 BGN. ""Please choose an option!\n";
                    cout<<"C-cancel account\n"<<"D-deposit\n"<<"L-logout\n"<<"T-transfer\n"<<"W-withdraw\n";
                    cin>>command;
                    while (command!="L"){
                        if(command=="D"){
                            cout<<"Please enter amount you want to deposit\n";
                            double money;
                            cin>>money;
                            while (money<=0){
                                cout<<"Please enter valid amount\n";
                                cin>>money;
                            }
                            balance[usersCount-1]=balance[usersCount-1]+money;
                            cout<<"Successfully deposited money\n";
                        } else if(command=="T") {
                            cout<<"Please enter amount you want to transfer and the name of the account\n";
                            double money;
                            int secondNameNumber;
                            string secondName;
                            bool doesItExist=false;
                            cin>>money;
                            while (money<=0){
                                cout<<"Please enter valid amount\n";
                                cin>>money;
                            }
                            cin>>secondName;
                            for(int i=0;i<usersCount;i++){
                                if(names[i]==secondName){
                                    doesItExist= true;
                                    break;
                                }
                            }
                            if(doesItExist){
                                secondNameNumber= findUsersNumber(secondName,names);
                                if(balance[usersCount-1]-money<-10000){
                                    cout<<"You don't have enough money\n";
                                } else {
                                    balance[usersCount-1]=balance[usersCount-1]-money;
                                    balance[secondNameNumber]=balance[secondNameNumber]+money;
                                    cout<<"Successfully transferred "<<money<<" BGN to "<<secondName<<endl;
                                }
                            } else {
                                cout<<"This account doesn't exist\n";
                            }


                        } else if(command=="W"){
                            cout<<"Please enter amount you want to withdraw\n";
                            double money;
                            cin>>money;
                            while (money<=0){
                                cout<<"Please enter valid amount\n";
                                cin>>money;
                            }
                            if(balance[usersCount-1]-money<-10000){
                                cout<<"You don't have enough money\n";
                            } else {
                                balance[usersCount-1]=balance[usersCount-1]-money;
                                cout<<"Successfully withdrawn "<<money<<" BGN\n";
                            }
                        } else if(command=="C"){
                            cout<<"Please enter password\n";
                            string tryPassword;
                            cin>>tryPassword;
                            if(hashedPassword(tryPassword)==passwords[usersCount-1]){
                                if(balance[usersCount-1]!=0){
                                    cout<<"Cannot cancel account, your balance is not 0 BGN\n";
                                } else{
                                    names[usersCount-1]="0";
                                    cout<<"Successfully canceled account\n";
                                    break;
                                }
                            } else {
                                cout<<"Invalid password\n";
                            }
                        } else {
                            cout<<"Please enter valid letter\n";
                        }
                        cout<<"You have "<<balance[usersCount-1]<<" BGN. Please choose an option!\n";
                        cout<<"C-cancel account\n"<<"D-deposit\n"<<"L-logout\n"<<"T-transfer\n"<<"W-withdraw\n";
                        cin>>command;
                    }
                }
            } else {
                cout<<"Please enter valid letter\n";
            }
            cout<<"Please choose an option!\n";
            cout<<"L-login\n"<<"R-register\n"<<"Q-quit\n";
            cin>>command;
        }
        my_file.open("users.txt");
        bool areThereUsers= false;
        for(int i=0;i<usersCount;i++){
            if(names[i]!="0"){
                my_file<<names[i]<<" "<<passwords[i]<<" "<<balance[i]<<endl;
                areThereUsers= true;
            }
        }
        if(!areThereUsers){
            clear();
        }
        my_file.close();
    }
}
