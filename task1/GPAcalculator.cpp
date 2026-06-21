#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Classes
class Course {
private:
    double gPoints;
    int cHours;
public:
    Course():gPoints(0),cHours(0) {}
    void setData(const string& grade,int ch) {
        // Setting Grade Points
        if( grade=="A+" || grade=="A") gPoints=4.00;
        else if(grade=="A-") gPoints=3.67;
        else if(grade=="B+") gPoints=3.33;
        else if(grade=="B" ) gPoints=3.00;
        else if(grade=="B-") gPoints=2.67;
        else if(grade=="C+") gPoints=2.33;
        else if(grade=="C" ) gPoints=2.00;
        else if(grade=="C-") gPoints=1.67;
        else if(grade=="D+") gPoints=1.33;
        else if(grade=="D" ) gPoints=1.00;
        else if(grade=="F" ) gPoints=0.00;
        else gPoints=-1;
        // Setting Credit Hours
        if(ch>0 && ch<7) cHours=ch;
        else             cHours=-1;
        // Checking Data Validity
        if(gPoints==-1 || cHours==-1)
            throw runtime_error("Invalid Inputs!\n");
    }
    double readGPoints()const { return gPoints; }
    int readCHours()const { return cHours; }
};
class Semester {
private:
    Course temp;
    vector<Course> c;
    double SGPA;
public:
    Semester():SGPA(0) {}
    void addCourse() {
        string grade;
        int cHours;
        cout<<"Enter Grade: "; cin>>grade;
        cout<<"Enter Credit Hours: "; cin>>cHours;
        temp.setData(grade,cHours);
        c.push_back(temp);
    }
    double sum(vector<double>& products) {
        double summation=0;
        for(size_t i=0;i<products.size();i++)
            summation+=products[i];
        return summation;
    }
    double sumCredits(vector<Course>& c) {
        double summation=0;
        for(size_t i=0;i<c.size();i++)
            summation+=c[i].readCHours();
        return summation;
    }
    vector<double> calculateProducts(vector<Course>& c) {
        vector<double> products;
        for(size_t i=0;i<c.size();i++) {
            products.push_back(c[i].readGPoints()*c[i].readCHours());
        }
        return products;
    }
    void SGPAcalculator(vector<Course>& c) {
        vector<double> products=calculateProducts(c);
        SGPA=sum(products)/sumCredits(c);
    }
    double readSGPA() {
        SGPAcalculator(c);
        return SGPA;
    }
};

// Helper Function
void results(vector<Semester>& s) {
    double SGPA,CGPA=0;
    cout<<"R\nesults :\n";
    for(size_t i=0;i<s.size();i++) {
        SGPA=s[i].readSGPA();
        CGPA+=SGPA;
        cout<<"Semester "<<i+1<<" SGPA : "<<SGPA<<'\n';
    }
    CGPA/=s.size();
    cout<<"CGPA : "<<CGPA;
}

// Main Function
int main() {
    unsigned int sems;
    unsigned int courses;
    cout<<"Enter Number of Semesters: "; cin>>sems;
    vector<Semester> s(sems);
    for(size_t i=0;i<s.size();i++) {
        cout<<"Enter Number of Courses for Semester "<<i+1<<" : "; cin>>courses;
        for(size_t j=0;j<courses;j++) {
            cout<<"\nCourse "<<j+1<<" :\n";
            s[i].addCourse();
        }
    }
    results(s);
}