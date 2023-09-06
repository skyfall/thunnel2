#include <iostream>

class ComplexData{
public:
    int a_;
    int b_;
    ComplexData(int a ,int b ):a_(a),b_(b){};
    ~ComplexData() = default;

    ComplexData& operator+(ComplexData& c){
        std::cout << "overload operator +";
        std::cout << "old a:" << a_ << "    old b: "<<b_ ;
        std::cout << "  comp_old a:" << c.a_ << "   comp_old b:"<<c.b_ <<std::endl;
        a_ = a_ + c.a_;
        b_ = b_ + c.b_;

        std::cout << "new_old a:" << a_ << "    new_old b: "<<b_ <<std::endl;
        return *this;
    }
};


int main(){
    ComplexData D1(1,2);
    ComplexData D2(3,4);

    ComplexData D3 = D1 + D2;


    std::cout << "D3.a :"<< D3.a_ <<"   D3.b:"<<D3.b_ << std::endl;
    // D1 + D2 +D1;
}