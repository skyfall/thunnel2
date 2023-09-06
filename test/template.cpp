#include <iostream>
#include <string>

template <typename A,typename B>
B Add(A a,B b){
    return a*b;
}

int main(){
    int a = 2;
    float b =10.97;
    std::string abc = "3333";
    
    std::string c_f = Add(a, abc);

    std::cout << c_f<< std::endl;

    int a = 10;
    const int* pa = &a;
    int* const pa2 = &a;
    a++;
}