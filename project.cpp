#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class bmsce{
    protected:
    string usn;
    char dept[4];
    public:
    bmsce(){
        usn="000";
    }
    void getdata1(){
        cout<<"Enter usn and department of the student\n";
        cin>>usn>>dept;
    }
    string retusn(){
        return usn;
    }
};
class department : public bmsce{
    protected:
    string courses[5];
    int marks[5];
    public:
    department(){
        for(int i=0;i<5;i++){
            courses[i]="XXX";
            marks[i]=0;
        }
    }
    void getdata2(){
        cout<<"Enter the core subject codes :\n";
        for(int i=0;i<3;i++){
            cin>>courses[i];
        }
    }
};
class student : public department{
    string name;
    float cgpa;

    public:
    student(){
        name="No Name";
        cgpa=0.0;
    }
    void getdata(){
        getdata1();
        cout<<"Enter student name : ";
        cin>>name;
        getdata2();
        cout<<"\nEnter elective courses : \n";
        cin>>courses[3]>>courses[4];
        for(int i=0;i<5;i++){
            cout<<"Enter marks in "<<courses[i]<<" : ";
            cin>>marks[i];
        }
    }
    void display(){
        cout<<"\n**************************************\n";
        cout<<"Name : "<<name<<endl;
        cout<<"USN : "<<usn<<endl;
        cout<<"Department : "<<dept<<endl;
        cout<<"Courses taken :\n";
        for(int i=0;i<5;i++){
            cout<<courses[i]<<"\t"<<marks[i];
        }
        cout<<"\nCGPA : "<<cgpa<<"\n";
    }
    void calc(){
        int sum=0;
        for(int i=0;i<5;i++){
            if(marks[i]>90)
                sum=sum+10;
            else if(marks[i]>80 && marks[i]<=90)
                sum=sum+9;
            else if(marks[i]>70 && marks[i]<=80)
                sum=sum+8;
            else if(marks[i]>60 && marks[i]<=70)
                sum=sum+7;
            else if(marks[i]>50 && marks[i]<=60)
                sum=sum+6;
            else if(marks[i]>40 && marks[i]<=50)
                sum=sum+5;
        }
        cgpa=(float)sum/5;
    }
    void create(){
        ofstream fout;
        fout.open("project.txt", ios::app | ios::out );
        fout.write((char *)this, sizeof(*this));
        fout.close();
    }
    void search(string id){
        int count=0;
        ifstream fin;
        fin.open("project.txt", ios::in );
        fin.read((char *)this, sizeof(*this));
        while(!fin.eof()){
            if(usn.compare(id) == 0){
                display();
                count++;
            }
            fin.read((char *)this, sizeof(*this));
        }
        if(count == 0)
            cout<<"\nRecord not found\n";
        fin.close();
    }
    void displayall(){
        ifstream fin;
        fin.open("project.txt", ios::in );
        fin.read((char *)this, sizeof(*this));
        while(!fin.eof()){
            display();
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
    }
    void del(string id){
        ifstream fin;
        ofstream fout;
        fin.open("project.txt", ios::app | ios::in);
        fout.open("temp.txt", ios::app | ios::in | ios::out);
        fin.read((char *)this, sizeof(*this));
        while(!fin.eof()){
            if(usn.compare(id))
                fout.write((char *)this, sizeof(*this));
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("project.txt");
        rename("temp.txt","project.txt");
    }
    void update(string id){
        fstream file;
        file.open("project.txt", ios::in | ios::out | ios::ate );
        file.seekg(0);
        file.read((char *)this, sizeof(*this));
        while(!file.eof()){
            if(usn.compare(id) == 0){
                getdata();
                file.seekp((int)file.tellp() - (int)sizeof(*this));
                file.write((char *)this, sizeof(*this));
            }
            file.read((char *)this, sizeof(*this));
        }
        file.close();
    }
};

int main(){
    string id;
    int num=1;
    student st;
    while(num){
        cout<<"\nMENU";
        cout<<"\n1. Create student record";
        cout<<"\n2. Search student record";
        cout<<"\n3. Display all student record";
        cout<<"\n4. Delete student record";
        cout<<"\n5. Modify student record";
        cout<<"\n0. Exit\n";
        cin>>num;
        
        switch(num){
            case 1:
                st.getdata();
                st.calc();
                st.create();
                cout<<"\nDetails recorded"<<endl;
                break;
            case 2:
                cout<<"Enter usn of student";
                cin.ignore();
                getline(cin,id);
                st.search(id);
                break;
            case 3:
                st.displayall();
                break;
            case 4:
                cout<<"Enter usn of student";
                cin.ignore();
                getline(cin,id);
                st.del(id);
                break;
            case 5:
                cout<<"Enter usn of student";
                cin.ignore();
                getline(cin,id);
                st.update(id);
                break;
            case 0:
                cout<<"Program exit"<<endl;
                break;
            default:
                cout<<"Wrong input"<<endl;
        }
    }
    return 0;
}