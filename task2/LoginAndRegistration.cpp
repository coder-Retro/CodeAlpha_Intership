#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <utility>
using namespace std;

// Classes
class Account {
private:
    string username;
    string password;
    string fileName;
    bool makeFile() {
        ofstream file(fileName);
        if(!file.is_open()) {
            cout<<"Error Creating File!\n";
            return false;
        }
        file<<username<<":"<<password;
        file.close();
        return true;
    }
public:
    Account(const string& un="N/A",const string& pw="N/A") {
        username=un;
        password=pw;
        fileName=un+".txt";
        if(un!="N/A") makeFile();
    }
    void setData(string un,string pw) {
        username=un;
        password=pw;
        deleteFile();
        fileName=un+".txt";
        makeFile();
    }
    bool readFile(const string& un) {
        string targetFile=un+".txt";
        if(!filesystem::exists(targetFile)) return false;
        ifstream file(targetFile);
        if(!file.is_open()) return false;
        string data;
        if(getline(file,data)) {
            size_t colon=data.find(":");
            if(colon!=string::npos) {   
                username=data.substr(0,colon);
                password=data.substr(colon+1);
                fileName=targetFile;
                file.close();
                return true;
            }
        }
        file.close();
        return true;
    }
    void deleteFile() {
        if(filesystem::exists(fileName))
            filesystem::remove(fileName);
    }
    string readUsername()const { return username; }
    bool matchPassword(string pw)const { return pw==password; }
    ~Account() {}
};

// Helper Function
bool isUsernameValid(const string& un) {
    return !filesystem::exists(un+".txt");
}
void addAccount() {
    string un,pw;
    cout<<"Username: "; cin>>un;
    cout<<"Password: "; cin>>pw;
    if(isUsernameValid(un)) {
        Account acc(un,pw);
        cout<<'\n'<<acc.readUsername()<<"'s Account Has Been Created.\n";
    }
    else {
        cout<<"\nUsername Already Taken!\n";
        return;
    }
}
bool authenticateAccount(Account& a) {
    string un, pw;
    cout << "Username: "; cin >> un;
    cout << "Password: "; cin >> pw;
    if (!a.readFile(un)) {
        cout << "\nAccount Not Found!\n";
        return false;
    }
    if (!a.matchPassword(pw)) {
        cout << "\nIncorrect Password!\n";
        return false;
    }
    return true;
}
void delAccount() {
    Account targetAcc;
    if(authenticateAccount(targetAcc)) {
        targetAcc.deleteFile();
        cout<<'\n'<<targetAcc.readUsername()<<"'s Account Has Been Deleted.\n";
    }
}
void enterAccount(Account& a) {
    string un=a.readUsername();
    cout<<"\nWelcome "<<un<<"!\n";
    int choice;
    bool logout=false;
    while( !logout ) {
        cout<<"\nMenu:\n";
        // Account Features Here
        cout<<"0. For Logout.\n";
        cout<<"\nYour Choice: "; cin>>choice;
        switch(choice) {
            // Feature's Function Calls Here
            case 0 : logout=true; break;
            default: cout<<"\nInvalid Choice!\n";
        }
    }
    cout<<'\n'<<un<<" is Logging Out ...\n";
}
void loginAccount() {
    Account targetAcc;
    if(authenticateAccount(targetAcc))
        enterAccount(targetAcc);
}

// Main Function
int main() {
    int choice;
    bool shutdown=false;
    while( !shutdown ) {
        cout<<"\nMenu:\n";
        cout<<"1. Create Account.\n";
        cout<<"2. Delete Account.\n";
        cout<<"3. Login Account.\n";
        cout<<"4. Exit.\n";
        cout<<"\nYour Choice: "; cin>>choice;
        switch(choice) {
            case 1 : addAccount();   break;
            case 2 : delAccount();   break;
            case 3 : loginAccount(); break;
            case 4 : shutdown=true;  break;
            default: cout<<"Invalid Choice!\n";
        }
    }
    cout<<"Exiting ...\n";
    return 0;
}