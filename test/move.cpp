#include <iostream>

using namespace std;


class Useless
{
private:
    int n;
    char* pc;
    static int ct;
    void ShowObject() const;
public:
    Useless();
    explicit Useless(int k);
    Useless(int k,char ch);
    Useless(const Useless& f);
    Useless(Useless&& f);
    ~Useless();
    Useless operator+(const Useless& f)const;
    void ShowData() const;
};

int Useless::ct = 0;

Useless::Useless(){
    ++ct;
    n = 0;
    pc = 0;
    cout << "default constructor called: number of Object:" << ct << endl;
}

Useless::Useless(int k):n(k){
    ++ct;
    cout << "int constructor called; number of object:" << ct <<endl;
    pc = new char[n];
    ShowObject();
}

Useless::Useless(int k,char ch):n(k){
    ++ct;
    cout << "int ,char constructor called ;number of object:" << ct <<endl;
    pc  = new char[n];
    for (int i =0 ; i <n ; i++)
        pc[i] = ch;
    
    ShowObject();
}

int aaaa ;

Useless::Useless(const Useless& f):n(f.n){

    ++ct;
    cout << "copy const called ;number of objects:" << ct <<endl;
    pc =  new char[n];
    for (int i=0 ; i < n ; i++)
        pc[i] = f.pc[i];
    // cout << "copy end" << endl;
    ShowObject();
}

Useless::Useless(Useless && f) : n(f.n){
    aaaa = ct;
    ++ct;
    cout << "move construcotr called;number of object:"<<ct << endl;
    pc  = f.pc;
    f.pc = nullptr;
    f.n = 0;
    ShowObject();
}

Useless::~Useless(){
    cout << "destructor called ;objects left:"<<--ct  <<endl;
    cout << "deleted object "<<  "Data address:"<<(void*)pc << "\n";
    ShowObject();
    delete []pc;
}

Useless Useless::operator+(const Useless& f)const {
    cout << "entering operator+() \n";
    Useless temp = Useless(n+f.n);
    for (int i=0 ; i < n ; i++)
        temp.pc[i] = pc[i];
    for (int i = 0 ; i < n ; i++){
        temp.pc[i] = f.pc[i -n];
    }

    cout << "temp object: \n";
    cout << "Leaving operator+()\n";
    cout<<" operator+ address:"<< &temp<<endl;
    return temp;
}

void Useless::ShowObject() const {
    cout << "Number of elements: "<<n;
    cout << "  Data address:" << (void*)pc<<endl;
}

void Useless::ShowData() const{
    if (n == 0)
        cout << "(object empty)";
    else   
        for(int i =0 ; i < n ;i ++)
            cout << pc[i];
    cout <<endl;
}

int main(){
    {
        Useless one(10,'x');
        Useless two = one;
        Useless three(20,'o');
        Useless four (two);

        // cout<<" one address:"<< &one<<endl;
        // cout<<" two address:"<< &two<<endl;
        // cout<<" three address:"<< &three<<endl;
        cout<<" four address:"<< &four<<endl;

        cout << "object One2:";
        one.ShowData();

        cout <<"object two:";
        two.ShowData();

        cout <<"object three:";
        three.ShowData();

        cout << "object four:";
        four.ShowData();
    }
}

