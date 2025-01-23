#include <iostream>

using namespace std;

int main(){
    int var1 = 20;
    int *ip; 

    ip = &var1;
    cout << "value of var variable:";
    cout << var1 << endl;

    cout << "var1 address:";
    cout << &var1 << endl;

    // ip
    cout << "address:";
    cout << ip << endl;

    // 指针对应的值
    cout << "value of *ip:";
    cout << *ip <<endl;

    return 0;

}