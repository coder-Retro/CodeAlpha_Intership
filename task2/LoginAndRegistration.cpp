#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Classes
class Account {
private:
    string username;
    string password;
public:
    Account(): username("N/A"), password("N/A") {}
    void setData(string un,string pw) {
        username=un;
        password=pw;
    }
    string readUsername()const { return username; }
    bool matchPassword(string pw)const { return pw==password; }
};

// Helper Function
bool isUsernameValid(vector<Account>& a,string un) {
    for(size_t i=0;i<a.size();i++)
        if( a[i].readUsername()==un ) return false;
    return true;
}
void addAccount(vector<Account>& a) {
    string un,pw;
    Account acc;
    cout<<"Username: "; cin>>un;
    cout<<"Password: "; cin>>pw;
    if(isUsernameValid(a,un))
        acc.setData(un,pw);
    else
    {
        cout<<"Username Already Taken!\n";
        return;
    }
    a.push_back(acc);
    cout<<a[a.size()-1].readUsername()<<"'s Account Has Been Created.\n";
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
        cout<<"Account Not Found!\n";
        return;
    }
    swap(a[target_Index],a[a.size()-1]);
    cout<<a[a.size()-1].readUsername()<<"'s Account Has Been Deleted.\n";
    a.pop_back();
}
void enterAccount(vector<Account>& a,int target_Index) {
    cout<<"Welcome "<<a[target_Index].readUsername()<<'\n';
    // Account Features Here
}
void loginAccount(vector<Account>& a) {
    int target_Index=searchAccount(a);
    if( target_Index==-1 ) {
        cout<<"Account Not Found!\n";
        return;
    }
    enterAccount(a,target_Index);
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
            case 1 : addAccount(acc); break;
            case 2 : delAccount(acc); break;
            case 3 : loginAccount(acc);   break;
            case 4 : shutdown=true;   break;
            default: cout<<"Invalid Choice!\n";
        }
    }
    cout<<"Exiting ...\n";
    return 0;
}