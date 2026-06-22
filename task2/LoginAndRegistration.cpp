#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
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
    void deleteFile() {
        if(filesystem::exists(fileName))
            filesystem::remove(fileName);
    }
    string readUsername()const { return username; }
    bool matchPassword(string pw)const { return pw==password; }
    ~Account() {}
};

// Helper Function
bool isUsernameValid(vector<Account>& a,string un) {
    for(size_t i=0;i<a.size();i++)
        if( a[i].readUsername()==un ) return false;
    return true;
}
void addAccount(vector<Account>& a) {
    string un,pw;
    cout<<"Username: "; cin>>un;
    cout<<"Password: "; cin>>pw;
    if(isUsernameValid(a,un)) {
        Account acc(un,pw);
        a.push_back(acc);
        cout<<'\n'<<a[a.size()-1].readUsername()<<"'s Account Has Been Created.\n";
    }
    else {
        cout<<"\nUsername Already Taken!\n";
        return;
    }
}
int searchAccount(vector<Account>& a) {
    string un,pw;
    cout<<"Username: "; cin>>un;
    cout<<"Password: "; cin>>pw;
    for(size_t i=0;i<a.size();i++)
        if( un==a[i].readUsername() && a[i].matchPassword(pw) )
            return i;
    return -1;
}
void delAccount(vector<Account>& a) {
    int target_Index=searchAccount(a);
    if( target_Index==-1 ) {
        cout<<"\nAccount Not Found!\n";
        return;
    }
    a[target_Index].deleteFile();
    cout<<'\n'<<a[target_Index].readUsername()<<"'s Account Has Been Deleted.\n";
    swap(a[target_Index],a[a.size()-1]);
    a.pop_back();
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
void loginAccount(vector<Account>& a) {
    int target_Index=searchAccount(a);
    if( target_Index==-1 ) {
        cout<<"\nAccount Not Found!\n";
        return;
    }
    enterAccount(a[target_Index]);
}

// Main Function
int main() {
    int choice;
    vector<Account> acc;
    bool shutdown=false;
    while( !shutdown ) {
        cout<<"\nMenu:\n";
        cout<<"1. Create Account.\n";
        cout<<"2. Delete Account.\n";
        cout<<"3. Login Account.\n";
        cout<<"4. Exit.\n";
        cout<<"\nYour Choice: "; cin>>choice;
        switch(choice) {
            case 1 : addAccount(acc);   break;
            case 2 : delAccount(acc);   break;
            case 3 : loginAccount(acc); break;
            case 4 : shutdown=true;     break;
            default: cout<<"Invalid Choice!\n";
        }
    }
    cout<<"Exiting ...\n";
    return 0;
}